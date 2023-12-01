```Here is the generated C++ bindings using Pybind11:

```cpp
#include <pybind11/pybind11.h>
#include "structural_scanner.h"

namespace py = pybind11;

PYBIND11_MODULE(structural_scanner, m) {
    py::class_<structural_scanner>(m, "StructuralScanner")
        .def(py::init<dom_parser_implementation&, stage1_mode>())
        .def("add_structural", &structural_scanner::add_structural)
        .def("validate_utf8_character", &structural_scanner::validate_utf8_character)
        .def("validate_string", &structural_scanner::validate_string)
        .def("is_whitespace_or_operator", &structural_scanner::is_whitespace_or_operator)
        .def("scan", &structural_scanner::scan);
}
```

Please note that you need to include the header files for `dom_parser_implementation`, `stage1_mode` and other required types in your original code. Also, make sure to link against the Pybind11 library when compiling your extension module.