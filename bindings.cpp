```cpp
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "FilesystemStream.h"

namespace py = pybind11;

PYBIND11_MODULE(FilesystemStream, m) {
    py::class_<FilesystemStream>(m, "FilesystemStream")
        .def(py::init<const std::string &, bool, const std::string &, const bool>())
        .def("getBlock", &FilesystemStream::getBlock)
        .def("getBlockIterator", &FilesystemStream::getBlockIterator)
        .def("getBlockTxt", &FilesystemStream::getBlockTxt)
        .def("writeBlock", &FilesystemStream::writeBlock)
        .def("writeValidFiles", &FilesystemStream::writeValidFiles)
        .def("currentSize", &FilesystemStream::currentSize)
        .def("isEmpty", &FilesystemStream::isEmpty)
        .def("getFilePath", &FilesystemStream::getFilePath)
        .def("getValidFilesBlock", &FilesystemStream::getValidFilesBlock)
        .def("endOfValidFiles", &FilesystemStream::endOfValidFiles)
        .def("getValidFilesPath", &FilesystemStream::getValidFilesPath)
        .def("getBlockSizeStr", &FilesystemStream::getBlockSizeStr)
        .def("getTmpPath", &FilesystemStream::getTmpPath)
        .def("getFileByIndex", &FilesystemStream::getFileByIndex)
        .def("getValidFilesSize", &FilesystemStream::getValidFilesSize)
        .def("getValidFilesSlice", &FilesystemStream::getValidFilesSlice);
}