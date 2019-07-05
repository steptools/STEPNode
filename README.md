# ARCHIVED 

Development of this package has moved internal to STEP Tools to be 
closer to the C++ operations that it wraps, but this GitHub repository
remains as a read-only reference. 

# STEPNode

The STEP-NC API provides high-level operations to create, manipulate,
and simulate digital thread models.  These operations are implemented
in C++ and wrapped with a Node Native Addon.  They are also available
as a .NET API for C\# and VB use.

The API has hundreds of functions which are grouped into several objects
that provide namespace segregation and some state. API calls are mostly
plain functions and there is no object heiarchy. The API is documented
[here](http://www.steptools.com/docs/stepnc_api/).

The [examples](examples/README.md) directory contains several examples
showing how to use the STEPNode interface to build digital thread
models from a variety of source material.

The STEPNode module is used by the digital thread server in the [NC.js
Package](https://github.com/steptools/NC.js/).

The master branch of this package is published to NPM as the STEPNode
package, but [BUILDING](BUILDING.md) describes how to compile the
package from source.

The [CONTRIBUTING](CONTRIBUTING.md) file describes the technical
details for adding new node native functions to the API and the
procedure for submiting them for inclusion.



