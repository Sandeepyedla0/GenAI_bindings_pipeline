
```cpp
#include <pybind11/pybind11.h>
#include "padded_string_view.h"

namespace py = pybind11;

PYBIND11_MODULE(padded_string_view_module, m) {
    py::class_<padded_string_view>(m, "padded_string_view")
        .def(py::init<>())
        .def(py::init<const char*, size_t, size_t>())
        .def(py::init<const uint8_t*, size_t, size_t>())
        .def(py::init<const std::string&>())
        .def(py::init<std::string_view, size_t>())
        .def("capacity", &padded_string_view::capacity)
        .def("remove_utf8_bom", &padded_string_view::remove_utf8_bom)
        .def("padding", &padded_string_view::padding);
}