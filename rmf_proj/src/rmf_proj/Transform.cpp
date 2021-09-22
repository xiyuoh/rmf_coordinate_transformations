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

#include <rmf_proj/Transform.hpp>
#include <proj.h>

namespace rmf_proj {

//==============================================================================
class Transform::Implementation
{
public:
  Implementation(const std::string& coordinate_system_1,
    const std::string& coordinate_system_2);

  ~Implementation();

  void transform_1_to_2(double x, double y, double& out_x, double& out_y);

  void transform_2_to_1(double x, double y, double& out_x, double& out_y);

  PJ_CONTEXT* _context = nullptr;
  PJ* _transform = nullptr;
};

//==============================================================================
Transform::Implementation::Implementation(const std::string& crs_1,
  const std::string& crs_2)
{
  _context = proj_context_create();
  _transform = proj_create_crs_to_crs(_context,
      crs_1.c_str(), crs_2.c_str(), nullptr);
}

//==============================================================================
Transform::Implementation::~Implementation()
{
  proj_destroy(_transform);
  proj_context_destroy(_context);
}

//==============================================================================
void Transform::Implementation::transform_1_to_2(double x, double y,
  double& out_x, double& out_y)
{
  PJ_COORD p1 = proj_coord(x, y, 0, 0);
  PJ_COORD p2 = proj_trans(_transform, PJ_FWD, p1);

  out_x = p2.v[0];
  out_y = p2.v[1];
}

//==============================================================================
void Transform::Implementation::transform_2_to_1(double x, double y,
  double& out_x, double& out_y)
{
  PJ_COORD p2 = proj_coord(x, y, 0, 0);
  PJ_COORD p1 = proj_trans(_transform, PJ_INV, p2);

  out_x = p1.v[0];
  out_y = p1.v[1];
}

//==============================================================================
Transform::Transform(const std::string& crs_1,
  const std::string& crs_2)
: _pimpl(rmf_utils::make_impl<Implementation>(crs_1, crs_2))
{
}

//==============================================================================
void Transform::transform_1_to_2(double x, double y, double& out_x,
  double& out_y)
{
  _pimpl->transform_1_to_2(x, y, out_x, out_y);
}

//==============================================================================
void Transform::transform_2_to_1(double x, double y, double& out_x,
  double& out_y)
{
  _pimpl->transform_2_to_1(x, y, out_x, out_y);
}

//==============================================================================
WGS84PseudoMercator_SVY21_Transform::WGS84PseudoMercator_SVY21_Transform()
: Transform("EPSG:3857", "EPSG:3414")
{
}

//==============================================================================
WGS84GPS_SVY21_Transform::WGS84GPS_SVY21_Transform()
: Transform("EPSG:4326", "EPSG:3414")
{
}

} // namespace rmf_proj