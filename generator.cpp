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

#include "generator.h"

void ScalarTypeGen::generate () {
    type_id = gen_policy->get_allowed_types().at(rand_val_gen->get_rand_value<int>(0, gen_policy->get_allowed_types().size() - 1));
}

void ModifierGen::generate () {
    modifier = gen_policy->get_allowed_modifiers().at(
               rand_val_gen->get_rand_value<int>(0, gen_policy->get_allowed_modifiers().size() - 1));
}

void StaticSpecifierGen::generate () {
    if (gen_policy->get_allow_static_var())
        specifier = rand_val_gen->get_rand_value<int>(0, 1);
    else
        specifier = false;
}

void DataGen::rand_init_param () {
    if (!rand_init)
        return;

    ScalarTypeGen scalar_type_gen (gen_policy);
    scalar_type_gen.generate ();
    type_id = scalar_type_gen.get_type ();

    ModifierGen modifier_gen (gen_policy);
    modifier_gen.generate ();
    modifier = modifier_gen.get_modifier ();

    StaticSpecifierGen static_spec_gen (gen_policy);
    static_spec_gen.generate ();
    static_spec = static_spec_gen.get_specifier ();
}

int ScalarVariableGen::variable_num = 0;

void ScalarVariableGen::generate () {
    rand_init_param ();
    Variable tmp_var ("var_" + std::to_string(variable_num), type_id, modifier, static_spec);
    data = std::make_shared<Variable> (tmp_var);
    variable_num++;
}

int ArrayVariableGen::array_num = 0;

void ArrayVariableGen::generate () {
    rand_init_param ();
    if (rand_init) {
        size = rand_val_gen->get_rand_value<int>(gen_policy->get_min_array_size(), gen_policy->get_max_array_size());
        essence = (Array::Ess) (gen_policy->get_essence_differ() ? rand_val_gen->get_rand_value<int>(0, Array::Ess::MAX_ESS - 1) :
                                                                   gen_policy->get_primary_essence());
    }
    Array tmp_arr ("arr_" + std::to_string(array_num), type_id, modifier, static_spec, size, essence);
    data = std::make_shared<Array> (tmp_arr);
    array_num++;
}

void DeclStmtGen::generate () {
    // TODO: Add non-scalar variables declaration
    if (rand_init) {
        // TODO: Enable
        //if (!gen_policy.set_allow_scalar_variables())
        // print error
        ScalarVariableGen scalar_var_gen (gen_policy);
        scalar_var_gen.generate ();
        data = scalar_var_gen.get_data();
        // TODO: Add auto-init generation
    }
    DeclStmt decl_stmt;
    decl_stmt.set_data (data);
    decl_stmt.set_init (init);
    decl_stmt.set_is_extern (is_extern);
    stmt = std::make_shared<DeclStmt> (decl_stmt);
}
