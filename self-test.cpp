/*
Copyright (c) 2015-2016, Intel Corporation

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

//////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include "type.h"

using namespace rl;

void self_test () {
    std::cout << "SELFTEST" << std::endl;

    std::shared_ptr<Type> bool_type = IntegerType::init(AtomicType::IntegerTypeID::BOOL);
    bool_type->dbg_dump();

    std::shared_ptr<Type> int_type = IntegerType::init(AtomicType::IntegerTypeID::INT, AtomicType::Mod::CONST, true, 32);
    int_type->dbg_dump();

    std::shared_ptr<StructType> struct_type = std::make_shared<StructType>("AA");
    struct_type->add_member(bool_type, "memb_1");
    struct_type->add_member(int_type, "memb_2");
    struct_type->dbg_dump();
}