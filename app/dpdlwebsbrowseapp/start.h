# File: app/dpdlwebsbrowseapp/start.h
#
# Example: Dpdl sample app 'DpdlWebsBrowseApp' that implements an embedded webserver (with C network library from Mongoose)
#			and a browser like UI to browse the contents provided by the webserver in a fully browswer like fashion
#
# Author: A.Costa
# e-mail: ac@dpdl.io
#
#

import('thread')
import("dpdllib.h")

func dpdl_javafx_start(object stage)
	stage.setTitle("Dpdl Web Browser")

	println("loading browser webview...")

	object browser = loadObj("WebView")
	browser.setContextMenuEnabled(true)
	browser.setJavaScriptEnabled(true)

	object web_engine = browser.getEngine()

	web_engine.load(listen_address)

	object color = getClass("paint.Color")

	object scene = loadObj("Scene", browser, width, height, color.web("#666970"))

	stage.setScene(scene)
	stage.show()
end

# main

double width = 850.0d
double height = 600.0d

string listen_address = "http://127.0.0.1:8000"
string content_dir = "./DpdlLibs/app/dpdlwebsbrowseapp/content"
string upload_dir = "./DpdlLibs/app/dpdlwebsbrowseapp/upload"

dpdl_stack_var_glob_put("webserver_ip", listen_address)
dpdl_stack_var_glob_put("webserver_dir", content_dir)
dpdl_stack_var_glob_put("webserver_upload_dir", upload_dir)
dpdl_stack_var_glob_put("enable_hexdump", "no")

println("DpdlWebsBrowseApp")

println("starting embedded webserver...")

int server = createThread(0, "app/dpdlwebsbrowseapp/dpdlEmbeddedWebserver.h", dpdlNormPriority, 100000)

if(server == dpdlTrue)
	println("server started correctly")
	println("")
	println("listening on address: " + listen_address)
else
	println("Error in starting server thread")
fi

sleep(2000)

println("starting browser UI web app...")

object runtime = getClass("Platform")
runtime.startup(thread.getRunnable())

object root = loadObj("scene.Group")
object style = root.getStyleClass()

style.add("browser")

println("starting App....")
object app = loadObj("DpdlJavaFXApp")
app.initApp()

