
```cpp
#include "ExternalMergeSort.h"
#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(external_merge_sort, m) {
    py::class_<ExternalMergeSort>(m, "ExternalMergeSort")
        .def(py::init<const Structure&, const std::string&, const std::string&, const std::string&, const std::string&, const int>())
        .def("currentSize", &ExternalMergeSort::currentSize)
        .def("writeTmpFile", &ExternalMergeSort::writeTmpFile)
        .def("sortFile", &ExternalMergeSort::sortFile)
        .def("sortMapFile", &ExternalMergeSort::sortMapFile)
        .def("mergeMaps", &ExternalMergeSort::mergeMaps)
        .def("writeFile", &ExternalMergeSort::writeFile)
        .def("merge", &ExternalMergeSort::merge)
        .def("writeMapTmpFile", &ExternalMergeSort::writeMapTmpFile)
        .def("getMapBlock", &ExternalMergeSort::getMapBlock)
        .def("twoWayMergeMaps", &ExternalMergeSort::twoWayMergeMaps);
}
```