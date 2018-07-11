#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP
#include <string>

typedef enum
{
	cast_int_to_double,
	cast_int_to_long,
	cast_float_to_double,
	jump,
	jump_if_true,
	jump_if_false,
	push_function,
	push_method,
	invoke,
	logical_and,
	logical_or,
	logical_not,

	add_int,
	sub_int,
	mul_int,
	div_int,
	mod_int,
	add_long,
	sub_long,
	mul_long,
	div_long,
	mod_long,
	add_float,
	sub_float,
	mul_float,
	div_float,
	add_double,
	sub_double,
	mul_double,
	div_double,
	minus_int,
	minus_long,
	minus_float,
	minus_double,
	gt_int,
	lt_int,
	ge_int,
	le_int,
	eq_int,
	ne_int,
	gt_long,
	lt_long,
	ge_long,
	le_long,
	eq_long,
	ne_long,
	gt_float,
	lt_float,
	ge_float,
	le_float,
	eq_float,
	ne_float,
	gt_double,
	lt_double,
	ge_double,
	le_double,
	eq_double,
	ne_double,
	eq_string,
	ne_string,
	eq_object,
	ne_object,
	push_constant_int,
	push_constant_long,
	push_constant_float,
	push_constant_double,
	push_constant_string,
	push_local_int,
	push_local_long,
	push_local_float,
	push_local_double,
	push_local_string,
	push_local_object,
	pop_local_int,
	pop_local_long,
	pop_local_float,
	pop_local_double,
	pop_local_string,
	pop_local_object,
	push_field_int,
	push_field_long,
	push_field_float,
	push_field_double,
	push_field_string,
	push_field_object,
	pop_field_int,
	pop_field_long,
	pop_field_float,
	pop_field_double,
	pop_field_string,
	pop_field_object,
	push_static_int,
	push_static_long,
	push_static_float,
	push_static_double,
	push_static_string,
	push_static_object,
	pop_static_int,
	pop_static_long,
	pop_static_float,
	pop_static_double,
	pop_static_string,
	pop_static_object,
	return_int,
	return_long,
	return_float,
	return_double,
	return_string,
	return_object
} Instruction;

typedef enum
{
	constant_int,
	constant_long,
	constant_float,
	constant_double,
	constant_char,
	constant_string
} ConstantPoolKind;

std::wstring InstructionToString(int instruction);
#endif // INSTRUCTION_HPP