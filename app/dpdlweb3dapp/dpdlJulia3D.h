# File: julia/dpdlJulia3D.h
#
# Example: This Dpdl code executes an embedded Julia script that creates and visualizes 3D scenes in the web browser with WebGL
#			via the julia 'MeshCat' package
#
# author: A.Costa
# e-mail: ac@dpdl.io
#
#

func create3DVisualization() int

	println("executing embedded julia code...")

	>>julia
	using MeshCat
	using GeometryBasics
	using CoordinateTransformations
	using ColorTypes

	println("starting 3D visualization...")

	vis = Visualizer()
	open(vis)

	setobject!(vis, HyperRectangle(Vec(0., 0, 0), Vec(1., 1, 1)))
	settransform!(vis, Translation(-0.5, -0.5, 0))

	verts = rand(Point3f, 100_000)
	colors = [RGB(p...) for p in verts]
	setobject!(vis, PointCloud(verts, colors))

	sleep(5)

	verts = rand(Point3f, 100_000)
	colors = [RGB(p...) for p in verts]
	setobject!(vis, PointCloud(verts, colors))

	while(true)
		println(".")
		sleep(4)
	end

	<<

	int exit_code = dpdl_exit_code()
	println("embedded julia exit code: " + exit_code)

	return exit_code
end

# main
println("testing 3D visualization in the web browser using julia...")

int res = create3DVisualization()

bool running = true
while(running)
	println(".")
	sleep(5000)
endwhile
