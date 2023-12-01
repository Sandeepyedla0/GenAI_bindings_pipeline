
Here is the C++ bindings code for the FilePattern class using Pybind11:

```cpp
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "FilePattern.h"

namespace py = pybind11;

PYBIND11_MODULE(FilePattern, m) {
    py::class_<FilePattern>(m, "FilePattern")
        .def(py::init<const std::string&, const std::string&, const std::string&, bool, bool>())
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

This code creates Python bindings for the FilePattern class using Pybind11. It exposes all the public member functions of the FilePattern class to Python. Note that you need to include the appropriate headers and link against the Pybind11 library when compiling this code.