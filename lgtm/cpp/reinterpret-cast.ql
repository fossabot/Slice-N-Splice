/**
 * @name Potential UB - reinterpret_cast<>()
 * @description Using reinterpret_cast<>() is, except in rare circumstance, UB-invoking
 *    Please do not use reinterpret_cast<>()
 * @kind problem
 * @problem.severity error
 * @precision medium
 * @id cpp/reinterpret-cast
 * @tags reliability
 *       correctness
 *       security
 */

import cpp
import Buffer
 
from ReinterpretCast cast_
where
  not cast_.isCompilerGenerated()
select cast_, "Potential UB - reinterpret_cast<>()"