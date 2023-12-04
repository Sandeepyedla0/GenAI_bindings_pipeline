
Here is the generated C++ bindings using Pybind11:

```cpp
#include <pybind11/pybind11.h>
#include "ChildFeatureAggregation.h"

namespace py = pybind11;

PYBIND11_MODULE(ChildFeatureAggregationModule, m) {
    py::class_<ChildFeatureAggregation>(m, "ChildFeatureAggregation")
        .def(py::init<>())
        .def(py::init<const char*>())
        .def("parse", &ChildFeatureAggregation::parse)
        .def_static("get_valid_options", &ChildFeatureAggregation::get_valid_options)
        .def("get_method", &ChildFeatureAggregation::get_method)
        .def("get_method_string", &ChildFeatureAggregation::get_method_string);

    py::enum_<Nyxus::AvailableChildFeatureAggregations>(m, "AvailableChildFeatureAggregations")
        .value("aNONE", Nyxus::AvailableChildFeatureAggregations::aNONE)
        .value("aSUM", Nyxus::AvailableChildFeatureAggregations::aSUM)
        .value("aMEAN", Nyxus::AvailableChildFeatureAggregations::aMEAN)
        .value("aMIN", Nyxus::AvailableChildFeatureAggregations::aMIN)
        .value("aMAX", Nyxus::AvailableChildFeatureAggregations::aMAX)
        .value("aWMA", Nyxus::AvailableChildFeatureAggregations::aWMA)
        .export_values();
}
```

Please note that you need to include the `ChildFeatureAggregation` header file in your project and make sure that Pybind11 is installed and configured correctly.