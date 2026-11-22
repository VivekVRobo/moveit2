/*********************************************************************
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2026, MoveIt Setup Assistant contributors
 *  All rights reserved.
 *********************************************************************/

#pragma once

#include <urdf/model.h>

namespace moveit_setup::controllers
{

/// Return the same scalar default-position rule used by MoveIt for bounded
/// single-DOF joints: zero when it is within bounds, otherwise the midpoint.
/// Joints without position limits retain zero as their default.
inline double getDefaultJointPosition(const urdf::Joint& joint)
{
  if (!joint.limits)
  {
    return 0.0;
  }

  if (joint.limits->lower <= 0.0 && joint.limits->upper >= 0.0)
  {
    return 0.0;
  }

  return (joint.limits->lower + joint.limits->upper) / 2.0;
}

}  // namespace moveit_setup::controllers
