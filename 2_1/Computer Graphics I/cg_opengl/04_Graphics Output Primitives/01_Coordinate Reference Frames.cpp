// To describe a picture, we first decide upon a convenient Cartesian coordinate
// system, called the world-coordinate reference frame, which could be either two-
// dimensional or three-dimensional. We then describe the objects in our picture by
// giving their geometric specifications in terms of positions in world coordinates.
// For instance, we define a straight-line segment with two endpoint positions, and
// a polygon is specified with a set of positions for its vertices. These coordinate
// positions are stored in the scene description along with other information about
// the objects, such as their color and their coordinate extents, which are the mini-
// mum and maximum x, y, and z values for each object. A set of coordinate extents
// is also described as a bounding box for an object. For a two-dimensional fig-
// ure, the coordinate extents are sometimes called an object’s bounding rectangle.
// Objects are then displayed by passing the scene information to the viewing rou-
// tines, which identify visible surfaces and ultimately map the objects to positions
// on the video monitor. The scan-conversion process stores information about the
// scene, such as color values, at the appropriate locations in the frame buffer, and
// the objects in the scene are displayed on the output device.