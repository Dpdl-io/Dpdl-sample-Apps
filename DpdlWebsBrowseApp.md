
# DpdlWebBrowseApp

![Dpdl](https://www.dpdl.io/images/dpdl-io.png)

				www.dpdl.io



## DpdlWebBrowseApp - an embedded Web-server with a web-browser UI

Application Dpdl source code:
[app/dpdlwebsbrowseapp](https://github.com/Dpdl-io/Dpdl-sample-Apps/tree/main/app/dpdlwebsbrowseapp)

This Dpdl applications implements a fully compliant http <ins>embedded Web-Server</ins> which is capable of serving web content from a defined local directory via HTTP protocol.

The applications provides also a <ins>Browser like User Interface (UI)</ins> to navigate the hosted web-sites. The browser supports most content creation technologies available in modern browsers (Html5, css, Javascript).

The applications makes use of the Mongoose C network library and of the JavaFX libraries.

Due to the fact that the mongoose C network library is compiled in memory at runtime by the Dpdl runtime (very fast compile time, 20 ms to compile and start the server), the application is completely cross platform.


As example web-site a dashboard (from Mongoose) for controlling IoT devices via MQTT protocol is presented.

**Web-server document root directory:**

<img src="https://www.dpdl.io/images/platform/examples/dpdlwebsbrowseapp/DpdlWebsBrowseApp_screen1.png" width="60%" height="60%">

**Dashboard IoT device management:**

<img src="https://www.dpdl.io/images/platform/examples/dpdlwebsbrowseapp/DpdlWebsBrowseApp_screen2.png" width="60%" height="60%">

<img src="https://www.dpdl.io/images/platform/examples/dpdlwebsbrowseapp/DpdlWebsBrowseApp_screen3.png" width="60%" height="60%">

**Upload page:**

<img src="https://www.dpdl.io/images/platform/examples/dpdlwebsbrowseapp/DpdlWebsBrowseApp_screen4.png" width="60%" height="60%">


