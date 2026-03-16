# DpdlMQTTApp - a simple sample application written with Dpdl
#
# (c)opyright 2023
# developed by SEE Solutions
#
# File: app/dpdlmqttapp/dpdlMqttUI.h
#
# Example: Dpdl UI app for MQTT client
#
# Author: A.Costa
# e-mail: ac@dpdl.io
#
#

func actionPerformed(string event)
	if(event == "Send_cmd")
		println("send")
		sendMsg()
	elsif(event == "Reset_cmd")
		println("reset")
	else
		println("command not found")
	fi
end


func addMsgToList(string msg_sent)
	data_model_list.addElement(msg_sent)
	int last_item = data_model_list.getSize()-1
	msg_list.ensureIndexIsVisible(last_item)

	object date = new("Date")
	date_str = date.toString()
	date_time.setText(date_str)
end

func sendMsg()
	println("sending message...")
	string text_msg = msg_area.getText()
	if(text_msg != "")
		MSG = text_msg
		MSG_STACK.push(MSG)
		msg_area.setText("")
		option_frame_class.showMessageDialog(frame, "Message sent successfully")
	fi

end

# main
int width = 550
int height = 500

object frame = new("JFrame", "DpdlMqttApp - www.dpdl.io")
object option_frame_class = getObj("JOptionPane")

object status_label = new("JLabel", "Status: ")

object data_model_list = new("DefaultListModel")
object msg_list = new("JList", data_model_list)
object msg_list_scroll =  new("JScrollPane")
msg_list_scroll.setViewportView(msg_list)

object border_layout_class = getObj("BorderLayout")

object layout_list1 = new("GridLayout")
object panel_list = new("JPanel", layout_list1)
panel_list.add(status_label)
panel_list.add(msg_list_scroll)
frame.add(panel_list, border_layout_class.NORTH)

object border_factory_class = getObj("BorderFactory")
object border_layout = new("BorderLayout")
object panel_text = new("JPanel", border_layout)


object msg_area = new("JTextArea", 220, 100)
object scroll_pane_class = getObj("JScrollPane")
object scroll_pane = new("JScrollPane", msg_area)
panel_text.setBorder(border_factory_class.createTitledBorder("Message:"))
panel_text.add(scroll_pane)
frame.add(panel_text, border_layout_class.CENTER)


object panel_form = new("JPanel")

object button = new("JButton")
object date_time = new("JLabel", "")
object topic_label = new("JLabel", "")

object event_listener = new("ActionListenerInterface")

button.setLabel("Send")
button.setActionCommand("Send_cmd");
button.addActionListener(event_listener)

panel_form.add(button)
panel_form.add(date_time)
panel_form.add(topic_label)

frame.add(panel_form, border_layout_class.SOUTH)

object frame_class = getObj("JFrame")
frame.setSize(width, height)
frame.setDefaultCloseOperation(frame_class.EXIT_ON_CLOSE);
frame.setVisible(true)

data_model_list.addElement("Message list->")

string MSG = ""
object MSG_STACK = new("Stack")
