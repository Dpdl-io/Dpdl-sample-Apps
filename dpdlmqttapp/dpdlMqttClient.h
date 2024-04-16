# DpdlMQTTApp - a simple sample application written with Dpdl
#
# (c)opyright 2023
# developed by SEE Solutions
#
# File: app/dpdlmqttapp/dpdlMqttClient.h
#
# Example: Dpdl sample app that implements a mqtt-client implemented in C with the mongoose library
#			The mongoose implementation is from the mongoose examples
#
# Author: A.Costa
# e-mail: ac@dpdl.io
#
#

# main
println("######################################################################################")
println("--------------------------------------------------------------------------------------")
println("## DpdlMQTTClient ##")
println("")
println("an embedded mqtt-client that is compiled and executed at runtime:)")
println("")
println("Dpdl example that implements a small embedded mqtt-client written in C using the Mongoose library")
println("")
println("--------------------------------------------------------------------------------------")


println("compiling and running mqtt client...")

dpdl_stack_push("dpdlstack:mongooseopt", "dpdl:-DMG_ENABLE_PACKED_FS=1", "dpdl:-F./DpdlLibs/app/dpdlmqttapp/packed_fs.c")
>>c
#include "mongoose.h"
#include "dpdl.h"

static const char *s_url = "{{server_addr}}";
static const char *s_sub_topic = "{{publish_topic}}";    // Pub topic
static const char *s_pub_topic = "{{subscribe_topic}}";  // Sub topic
static int s_qos = 1;   // MQTT QoS
static struct mg_connection *s_conn;

static int s_signo;
static void signal_handler(int signo) {
  s_signo = signo;
}

static void fn(struct mg_connection *c, int ev, void *ev_data) {
  if (ev == MG_EV_OPEN) {
    MG_INFO(("%lu CREATED", c->id));
  } else if (ev == MG_EV_CONNECT) {
    if (mg_url_is_ssl(s_url)) {
      struct mg_tls_opts opts = {.ca = mg_unpacked("./certs/ca.pem"),
                                 .name = mg_url_host(s_url)};
      mg_tls_init(c, &opts);
    }
  } else if (ev == MG_EV_ERROR) {
    MG_ERROR(("%lu ERROR %s", c->id, (char *) ev_data));
  } else if (ev == MG_EV_MQTT_OPEN) {
    // MQTT connect is successful
	// we add the connection to the dpdl stack
	struct dpdl_stack_data *conn_client = malloc(sizeof(struct dpdl_stack_data));
	conn_client->id = 23;
	conn_client->data = c;
	strcpy(conn_client->name, "MQTT conn");
	dpdl_stack_data_put(conn_client);

    struct mg_str subt = mg_str(s_sub_topic);
    struct mg_str pubt = mg_str(s_pub_topic), data = mg_str("Hello from DpdlMQTTApp");
    MG_INFO(("%lu CONNECTED to %s", c->id, s_url));
    struct mg_mqtt_opts sub_opts;
    memset(&sub_opts, 0, sizeof(sub_opts));
    sub_opts.topic = subt;
    sub_opts.qos = s_qos;
    mg_mqtt_sub(c, &sub_opts);
    MG_INFO(("%lu SUBSCRIBED to %.*s", c->id, (int) subt.len, subt.ptr));
    struct mg_mqtt_opts pub_opts;
    memset(&pub_opts, 0, sizeof(pub_opts));
    pub_opts.topic = pubt;
    pub_opts.message = data;
    pub_opts.qos = s_qos, pub_opts.retain = false;
    mg_mqtt_pub(c, &pub_opts);
    MG_INFO(("%lu PUBLISHED %.*s -> %.*s", c->id, (int) data.len, data.ptr,
             (int) pubt.len, pubt.ptr));
  } else if (ev == MG_EV_MQTT_MSG) {
    struct mg_mqtt_message *mm = (struct mg_mqtt_message *) ev_data;
    MG_INFO(("%lu RECEIVED %.*s <- %.*s", c->id, (int) mm->data.len,
             mm->data.ptr, (int) mm->topic.len, mm->topic.ptr));

	struct dpdl_stack_data *msg_client = malloc(sizeof(struct dpdl_stack_data));
	char msg_rcv[256];
	sprintf(msg_rcv, "%s",  mm->data.ptr);
	msg_client->id = 888;
	msg_client->data = msg_rcv;
	msg_client->data_len = (int) mm->data.len;

	dpdl_stack_data_put(msg_client);

  } else if (ev == MG_EV_CLOSE) {
    MG_INFO(("%lu CLOSED", c->id));
    s_conn = NULL;
  }
}

// recreate the connection if closed
static void timer_fn(void *arg) {
  struct mg_mgr *mgr = (struct mg_mgr *) arg;
  struct mg_mqtt_opts opts = {.clean = true,
                              .qos = s_qos,
                              .topic = mg_str(s_pub_topic),
                              .version = 4,
                              .message = mg_str("good bye")};
  if (s_conn == NULL) s_conn = mg_mqtt_connect(mgr, s_url, &opts, fn, NULL);

}

int main(int argc, char *argv) {
  printf("MQTT Client init()\n");

  struct mg_mgr mgr;
  int i;

  signal(SIGINT, signal_handler);
  signal(SIGTERM, signal_handler);

  mg_mgr_init(&mgr);
  mg_timer_add(&mgr, 3000, MG_TIMER_REPEAT | MG_TIMER_RUN_NOW, timer_fn, &mgr);
  while (s_signo == 0) mg_mgr_poll(&mgr, 1000);
  mg_mgr_free(&mgr);

  return 0;
}
<<

int exit_code = dpdl_exit_code()
println("mqtt-client exit code: " + exit_code)

