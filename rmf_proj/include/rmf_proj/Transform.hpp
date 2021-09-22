/*
 * Copyright (C) 2021 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/

#ifndef RMF_PROJ__RMF_PROJ_HPP
#define RMF_PROJ__RMF_PROJ_HPP

#include <rmf_utils/impl_ptr.hpp>
#include <string>

namespace rmf_proj {

//==============================================================================
// Generic transform between arbitrary coordinate systems
class Transform
{
public:
  /// Constructor
  /// See https://proj.org/development/reference/functions.html#c.proj_create_crs_to_crs
  ///
  /// \param[in] crs_1
  ///   Coordinate reference system 1
  ///
  /// \param[in] crs_2
  ///   Coordinate reference system
  Transform(const std::string& crs_1,
    const std::string& crs_2);

  /// Transform input coordinate from crs_1 to crs_2
  ///
  /// \param[in] x
  ///   First component of the input coordinate
  /// \param[in] y
  ///   Second component of the input coordinate
  /// \param[in] out_x
  ///   First component of the output coordinate
  /// \param[in] out_y
  ///   Second component of the output coordinate
  void transform_1_to_2(double x, double y, double& out_x, double& out_y);

  /// Transform input coordinate from crs_2 to crs_1
  ///
  /// \param[in] x
  ///   First component of the input coordinate
  /// \param[in] y
  ///   Second component of the input coordinate
  /// \param[in] out_x
  ///   First component of the output coordinate
  /// \param[in] out_y
  ///   Second component of the output coordinate
  void transform_2_to_1(double x, double y, double& out_x, double& out_y);

  class Implementation;

private:
  rmf_utils::impl_ptr<Implementation> _pimpl;
};

//==============================================================================
// Utility transforms for targeting SVY21 cartesian systems, or EPSG:3414
// SVY21 Reference: https://epsg.io/3414

// WGS84 Pseudo Mercator Reference: https://epsg.io/3857
class WGS84PseudoMercator_SVY21_Transform : public Transform
{
public:
  // Same as Transform("EPSG:3857", "EPSG:3414")
  WGS84PseudoMercator_SVY21_Transform();
};

// WGS84 GPS Reference: https://epsg.io/3857
class WGS84GPS_SVY21_Transform : public Transform
{
public:
  // Same as Transform("EPSG:4326", "EPSG:3414")
  WGS84GPS_SVY21_Transform();
};


} // namespace rmf_proj

#endif  // RMF_PROJ__RMF_PROJ_HPP
