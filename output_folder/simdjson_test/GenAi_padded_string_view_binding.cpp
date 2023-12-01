
Here is the generated C++ binding using Pybind11:

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
```

This code creates Python bindings for the `padded_string_view` class using Pybind11. It exposes all the constructors and methods of the `padded_string_view` class to Python. Note that you need to include the appropriate header files and link against the Pybind11 library when compiling this code.