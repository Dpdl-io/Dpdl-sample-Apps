
# DpdlWebBrowseApp

![Dpdl](https://www.dpdl.io/images/dpdl-io.png)

				www.dpdl.io



## DpdlWebBrowseApp - an embedded Web-server with a web-browser UI

**Dpdl source code**:
[app/dpdlwebsbrowseapp](https://github.com/Dpdl-io/Dpdl-sample-Apps/tree/main/app/dpdlwebsbrowseapp)

This Dpdl applications implements a fully compliant http <ins>embedded Web-Server</ins> which is capable of serving web content from a defined local directory via HTTP protocol.

The applications provides also a <ins>Browser like User Interface (UI)</ins> to navigate the hosted web-sites. The browser window supports most content creation technologies available in modern browsers (Html5, css, Javascript) and prvides navigation (reload page, back) and copy/paste of content.

The applications makes use of the Mongoose C network library for the web-server and of the JavaFX libraries for the UI.

The mongoose C network library used to implement the embedded web-server is compiled in memory at runtime by the Dpdl runtime (very fast compile time, 20 ms to compile and start the server). This makes the application completely cross platform without the need to compile native components.

As example web-site, the web-server hosts a dashboard (provided by Mongoose example) for controlling IoT devices via MQTT protocol.

**Web-server document root directory listing:**

<img src="https://www.dpdl.io/images/platform/examples/dpdlwebsbrowseapp/DpdlWebsBrowseApp_screen1.png" width="60%" height="60%">

**Dashboard IoT device management:** (from Mongoose example)

<img src="https://www.dpdl.io/images/platform/examples/dpdlwebsbrowseapp/DpdlWebsBrowseApp_screen2.png" width="60%" height="60%">

<img src="https://www.dpdl.io/images/platform/examples/dpdlwebsbrowseapp/DpdlWebsBrowseApp_screen3.png" width="60%" height="60%">

**Upload page:**

<img src="https://www.dpdl.io/images/platform/examples/dpdlwebsbrowseapp/DpdlWebsBrowseApp_screen4.png" width="60%" height="60%">


