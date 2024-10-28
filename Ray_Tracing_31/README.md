The first version which is able to read a polygons, triangles and material information from obj and mtl files.

 Several new classes were added

 1 ==> obj_model_reader to read the obj and mtl files and add the information to the world.

 2 ==> mesh to consider polygons with the normal vectors and edge coordinates read from the obj file.

 3 ==> triangle_mesh which is derived from the mesh class to manipulate triangles

 4 ==> general in the material.h to handle the general material format read from the mtl files (Work in progress)

 

