// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from dro_hg:msg/LowState.idl
// generated code does not contain a copyright notice
#include "dro_hg/msg/detail/low_state__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `motor_state`
#include "dro_hg/msg/detail/motor_state__functions.h"

bool
dro_hg__msg__LowState__init(dro_hg__msg__LowState * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    dro_hg__msg__LowState__fini(msg);
    return false;
  }
  // slave_num
  // motor_state
  if (!dro_hg__msg__MotorState__Sequence__init(&msg->motor_state, 0)) {
    dro_hg__msg__LowState__fini(msg);
    return false;
  }
  return true;
}

void
dro_hg__msg__LowState__fini(dro_hg__msg__LowState * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // slave_num
  // motor_state
  dro_hg__msg__MotorState__Sequence__fini(&msg->motor_state);
}

bool
dro_hg__msg__LowState__are_equal(const dro_hg__msg__LowState * lhs, const dro_hg__msg__LowState * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  // slave_num
  if (lhs->slave_num != rhs->slave_num) {
    return false;
  }
  // motor_state
  if (!dro_hg__msg__MotorState__Sequence__are_equal(
      &(lhs->motor_state), &(rhs->motor_state)))
  {
    return false;
  }
  return true;
}

bool
dro_hg__msg__LowState__copy(
  const dro_hg__msg__LowState * input,
  dro_hg__msg__LowState * output)
{
  if (!input || !output) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  // slave_num
  output->slave_num = input->slave_num;
  // motor_state
  if (!dro_hg__msg__MotorState__Sequence__copy(
      &(input->motor_state), &(output->motor_state)))
  {
    return false;
  }
  return true;
}

dro_hg__msg__LowState *
dro_hg__msg__LowState__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  dro_hg__msg__LowState * msg = (dro_hg__msg__LowState *)allocator.allocate(sizeof(dro_hg__msg__LowState), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(dro_hg__msg__LowState));
  bool success = dro_hg__msg__LowState__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
dro_hg__msg__LowState__destroy(dro_hg__msg__LowState * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    dro_hg__msg__LowState__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
dro_hg__msg__LowState__Sequence__init(dro_hg__msg__LowState__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  dro_hg__msg__LowState * data = NULL;

  if (size) {
    data = (dro_hg__msg__LowState *)allocator.zero_allocate(size, sizeof(dro_hg__msg__LowState), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = dro_hg__msg__LowState__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        dro_hg__msg__LowState__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
dro_hg__msg__LowState__Sequence__fini(dro_hg__msg__LowState__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      dro_hg__msg__LowState__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

dro_hg__msg__LowState__Sequence *
dro_hg__msg__LowState__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  dro_hg__msg__LowState__Sequence * array = (dro_hg__msg__LowState__Sequence *)allocator.allocate(sizeof(dro_hg__msg__LowState__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = dro_hg__msg__LowState__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
dro_hg__msg__LowState__Sequence__destroy(dro_hg__msg__LowState__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    dro_hg__msg__LowState__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
dro_hg__msg__LowState__Sequence__are_equal(const dro_hg__msg__LowState__Sequence * lhs, const dro_hg__msg__LowState__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!dro_hg__msg__LowState__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
dro_hg__msg__LowState__Sequence__copy(
  const dro_hg__msg__LowState__Sequence * input,
  dro_hg__msg__LowState__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(dro_hg__msg__LowState);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    dro_hg__msg__LowState * data =
      (dro_hg__msg__LowState *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!dro_hg__msg__LowState__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          dro_hg__msg__LowState__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!dro_hg__msg__LowState__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
