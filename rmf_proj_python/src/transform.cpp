#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <rmf_proj/Transform.hpp>

#include <iostream>
#include <vector>

namespace py = pybind11;

PYBIND11_MODULE(rmf_transform, m) {
  py::class_<rmf_proj::Transform>(m, "Transform")
  .def(py::init<const std::string &, const std::string &>())
  .def("transform_1_to_2",
    [](rmf_proj::Transform& self, double x, double y, double& out_x, double& out_y)
    {
      self.transform_1_to_2(x, y, out_x, out_y);
      std::vector<float> out_crs;
      out_crs.push_back(out_x);
      out_crs.push_back(out_y);
      return out_crs;
    })
  .def("transform_2_to_1",
    [](rmf_proj::Transform& self, double x, double y, double& out_x, double& out_y)
    {
      self.transform_2_to_1(x, y, out_x, out_y);
      std::vector<float> out_crs;
      out_crs.push_back(out_x);
      out_crs.push_back(out_y);
      return out_crs;
    });
}