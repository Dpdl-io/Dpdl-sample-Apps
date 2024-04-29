# DpdlMQTTApp - a simple sample application written with Dpdl
#
# (c)opyright 2023
# developed by SEE Solutions
#
# File: app/dpdlmqttapp/start.h
#
# Example: Dpdl startup script for dpdl sample app 'DpdlMQTTApp' that implements an embedded mqtt-server implemented in C with the Mongoose library
#
# Author: A.Costa
# e-mail: ac@dpdl.io
#
#

include("dpdlMqttUI.h")
import("dpdllib.h")


func clientMqttPublish(int t_id)
	println("Client publish process started with id: " + t_id)

	string message = ""
	string msg_to_sent = ""

	bool is_empty = MSG_STACK.empty()
	if(is_empty == false)
		println("New message available to send")
		msg_to_sent = MSG_STACK.pop()
		message = msg_to_sent
	else
		message = "MEGA Hello Mqtt msg from Dpdl " + msg_counter + " "
	fi

	dpdl_stack_obj_put("conn_id", connection_id)
	dpdl_stack_obj_put("msg_to_send", message)

	dpdl_stack_push("dpdlstack:mongooseopt", "dpdlbuf_msg_rcv", "dpdl:-DMG_ENABLE_PACKED_FS=1", "dpdl:-F./DpdlLibs/app/dpdlmqttapp/packed_fs.c")
	>>c
	#include "stdio.h"
	#include "mongoose.h"
	#include "dpdl.h"

	extern void dpdl_stack_buf_put(char *buf);

	static const char *s_sub_topic = "{{publish_topic}}"; //topic

	static int s_qos = 1; // QoS

	int connect_id = {{conn_id}};

	static struct mg_connection *s_conn = NULL;

	struct dpdl_stack_data *get_connection(int conn_id){
	    return dpdl_stack_data_get(conn_id);
	}

	char *getMsgRecieved(){
		struct dpdl_stack_data *msg_d = dpdl_stack_data_get(888);
		char msg_rcv[256];
		if(msg_d != NULL){
			printf("data id: %d\n", msg_d->id);
			printf("data len: %d\n", msg_d->data_len);
			strcpy(&msg_rcv, msg_d->data);
		}
		return &msg_rcv;
	}

	int main(int argc, char *argv) {
		printf("publishing message '{{msg_to_send}}\n'");
		struct dpdl_stack_data *conn = get_connection(connect_id);
		if(conn != NULL){
			printf("connection: %d active\n", conn->id);
			printf("name: %s\n", conn->name);

			if (s_conn == NULL) s_conn = conn->data;

			struct mg_mqtt_opts pub_opts = {.topic = mg_str("{{publish_topic}}"),
			                                .message = mg_str("{{msg_to_send}}"),
			                                .qos = 1,
			                                .retain = false};
			mg_mqtt_pub(s_conn, &pub_opts);

			printf("message published!!:)\n");

			printf("getting last received message...\n");
			char *msg__ = getMsgRecieved();

			dpdl_stack_buf_put(msg__);

			return 0;
		}else{
			printf("connection is NULL, waiting for connection to be active...\n");
			return -1;
		}
	}
	<<
	int exit_code = dpdl_exit_code()
	println("embedded C exit code: " + exit_code)

	if(exit_code == 0)
		string message_received = dpdl_stack_buf_get("dpdlbuf_msg_rcv")

		addMsgToList(message_received)
	fi

	msg_counter = msg_counter+1
	MSG = ""
end

# main
println("starting embedded MQTT Server...")

int connection_id = 23
int msg_counter = 0

string mqtt_server_address = "mqtt://127.0.0.1:1883"
string mqtt_pub_topic = "dpdl/+/test"
string mqtt_sub_topic = "dpdl/clnt/test"

dpdl_stack_var_glob_put("server_addr", mqtt_server_address)
dpdl_stack_var_glob_put("publish_topic", mqtt_pub_topic)
dpdl_stack_var_glob_put("subscribe_topic", mqtt_sub_topic)


dpdl_stack_push("dpdlstack:mongooseopt", "dpdl:applyvars", "dpdl:compile", "dpdl:-DMG_ENABLE_LINES=1", "dpdl:-I./DpdlLibs/app/dpdlmqttapp/include", "dpdl:-I./DpdlLibs/app/dpdlmqttapp/mongoose", "dpdl:-I./DpdlLibs/app/dpdlmqttapp/mongoose/src", "dpdl:-A./DpdlLibs/app/dpdlmqttapp/mongoose/src")

int server = createThread(0, "app/dpdlmqttapp/dpdlMqttServer.h", dpdlNormPriority, 100000)

string status_msg = ""
if(server == dpdlTrue)
	status_msg = "mqtt-server started successfully"
	println(status_msg)
else
	status_msg = "Error in starting mqtt-server thread"
	println(status_msg)
	exit(-1)
fi

status_label.setText("Status: " + status_msg)
topic_label.setText("Pub Topic: '" + mqtt_pub_topic + "' : Sub Topic: '" + mqtt_sub_topic + "'")

sleep(5000)

println("starting MQTT Client...")


int client = createThread(1, "app/dpdlmqttapp/dpdlMqttClient.h", dpdlNormPriority, 100000)

raise(client, "Error in starting mqtt-client")

println("mqtt-client started successfully")


println("starting mqtt client publisher process...")

int tid = Thread("clientMqttPublish", 5000)

raise(tid, "Error in starting client publishing thread")

println("mqtt client publishing process started successfully with thread id: " + tid)

