// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from dro_hg:msg/LegState.idl
// generated code does not contain a copyright notice

#ifndef DRO_HG__MSG__DETAIL__LEG_STATE__FUNCTIONS_H_
#define DRO_HG__MSG__DETAIL__LEG_STATE__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "dro_hg/msg/rosidl_generator_c__visibility_control.h"

#include "dro_hg/msg/detail/leg_state__struct.h"

/// Initialize msg/LegState message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * dro_hg__msg__LegState
 * )) before or use
 * dro_hg__msg__LegState__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_dro_hg
bool
dro_hg__msg__LegState__init(dro_hg__msg__LegState * msg);

/// Finalize msg/LegState message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_dro_hg
void
dro_hg__msg__LegState__fini(dro_hg__msg__LegState * msg);

/// Create msg/LegState message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * dro_hg__msg__LegState__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_dro_hg
dro_hg__msg__LegState *
dro_hg__msg__LegState__create();

/// Destroy msg/LegState message.
/**
 * It calls
 * dro_hg__msg__LegState__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_dro_hg
void
dro_hg__msg__LegState__destroy(dro_hg__msg__LegState * msg);

/// Check for msg/LegState message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_dro_hg
bool
dro_hg__msg__LegState__are_equal(const dro_hg__msg__LegState * lhs, const dro_hg__msg__LegState * rhs);

/// Copy a msg/LegState message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_dro_hg
bool
dro_hg__msg__LegState__copy(
  const dro_hg__msg__LegState * input,
  dro_hg__msg__LegState * output);

/// Initialize array of msg/LegState messages.
/**
 * It allocates the memory for the number of elements and calls
 * dro_hg__msg__LegState__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_dro_hg
bool
dro_hg__msg__LegState__Sequence__init(dro_hg__msg__LegState__Sequence * array, size_t size);

/// Finalize array of msg/LegState messages.
/**
 * It calls
 * dro_hg__msg__LegState__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_dro_hg
void
dro_hg__msg__LegState__Sequence__fini(dro_hg__msg__LegState__Sequence * array);

/// Create array of msg/LegState messages.
/**
 * It allocates the memory for the array and calls
 * dro_hg__msg__LegState__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_dro_hg
dro_hg__msg__LegState__Sequence *
dro_hg__msg__LegState__Sequence__create(size_t size);

/// Destroy array of msg/LegState messages.
/**
 * It calls
 * dro_hg__msg__LegState__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_dro_hg
void
dro_hg__msg__LegState__Sequence__destroy(dro_hg__msg__LegState__Sequence * array);

/// Check for msg/LegState message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_dro_hg
bool
dro_hg__msg__LegState__Sequence__are_equal(const dro_hg__msg__LegState__Sequence * lhs, const dro_hg__msg__LegState__Sequence * rhs);

/// Copy an array of msg/LegState messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_dro_hg
bool
dro_hg__msg__LegState__Sequence__copy(
  const dro_hg__msg__LegState__Sequence * input,
  dro_hg__msg__LegState__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // DRO_HG__MSG__DETAIL__LEG_STATE__FUNCTIONS_H_
