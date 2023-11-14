#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>

#include "include/filepattern.h"

namespace py = pybind11;

PYBIND11_MAKE_OPAQUE(std::vector<Tuple>);

PYBIND11_MODULE(backend, m) {
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
    //    .def("setGroup", &FilePattern::setGroup)
    //  .def("setGroup", &FilePattern::setGroup)
        .def("next", &FilePattern::next)
        .def("nextGroup", &FilePattern::nextGroup)
        .def("currentBlockLength", &FilePattern::currentBlockLength)
        .def("getNewNaming", &FilePattern::getNewNaming)
        .def("getSlice", &FilePattern::getSlice)
        .def("getSliceByIdx", &FilePattern::getSliceByIdx)
//        .def_static("inferPattern", &FilePattern::inferPattern)
        .def("getMatchingBlock", &FilePattern::getMatchingBlock)
        .def("getItem", &FilePattern::getItem)
        .def("getItemList", &FilePattern::getItemList)
        .def("begin", &FilePattern::begin)
        .def("end", &FilePattern::end)
        .def("getSize", &FilePattern::getSize)
        .def("length", &FilePattern::length)
        .def("getPattern", &FilePattern::getPattern)
        .def("setPattern", &FilePattern::setPattern)
        .def("getPath", &FilePattern::getPath)
//        .def("getPatternObject", &FilePattern::getPatternObject, py::return_value_policy::reference);
};