
Here is the CPP output code using Pybind11 to generate Python bindings for the given C++ class "FilePattern":

```cpp
#include <pybind11/pybind11.h>
#include <pybind11/stl.h> // needed for automatic conversion of STL containers
#include "FilePattern.h"

namespace py = pybind11;

PYBIND11_MODULE(filepattern, m) {
    py::class_<FilePattern>(m, "FilePattern")
        .def(py::init<const std::string &, const std::string &, const std::string &, bool, bool>())
        .def("getMatchingByMap", &FilePattern::getMatchingByMap)
        .def("getFiles", &FilePattern::getFiles)
        .def("getMatching", &FilePattern::getMatching)
        .def("getOccurrences", &FilePattern::getOccurrences)
        .def("getOccurrencesByMap", &FilePattern::getOccurrencesByMap)
        .def("getUniqueValues", &FilePattern::getUniqueValues)
        .def("outputName", &FilePattern::outputName)
        .def("getVariables", &FilePattern::getVariables)
        .def("groupBy", &FilePattern::groupBy)
        .def("group", &FilePattern::group)
        .def("setGroup", &FilePattern::setGroup)
        .def("setGroup", &FilePattern::setGroup)
        .def("next", &FilePattern::next)
        .def("nextGroup", &FilePattern::nextGroup)
        .def("currentBlockLength", &FilePattern::currentBlockLength)
        .def("getNewNaming", &FilePattern::getNewNaming)
        .def("getSlice", &FilePattern::getSlice)
        .def("getSliceByIdx", &FilePattern::getSliceByIdx)
        .def("inferPattern", &FilePattern::inferPattern)
        .def("getMatchingBlock", &FilePattern::getMatchingBlock)
        .def("getItem", &FilePattern::getItem)
        .def("getItemList", &FilePattern::getItemList)
        .def("begin", &FilePattern::begin)
        .def("end", &FilePattern::end)
        .def("getSize", &FilePattern::getSize)
        .def("getGroupedSize", &FilePattern::getGroupedSize)
        .def("length", &FilePattern::length)
        .def("getGroupedSliceByIdx", &FilePattern::getGroupedSliceByIdx)
        .def("getPattern", &FilePattern::getPattern)
        .def("setPattern", &FilePattern::setPattern)
        .def("getPath", &FilePattern::getPath)
        .def("getPatternObject", &FilePattern::getPatternObject, py::return_value_policy::reference);
}
```

This code creates a Python module named 'filepattern', and it exposes the 'FilePattern' class with all its methods to Python. The methods are exposed in such a way that they can be called directly from Python. Note that you need to include the necessary headers and link against the Pybind11 library when compiling this code.