/*
* Covariant Script Sqlite Extension
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
* Copyright (C) 2019 Michael Lee(李登淳)
* Email: mikecovlee@163.com
* Github: https://github.com/mikecovlee
*/
#include <sqlite/sqlite.hpp>

static cs::namespace_t sqlite_db_ext=cs::make_shared_namespace<cs::name_space>();
static cs::namespace_t sqlite_stmt_ext=cs::make_shared_namespace<cs::name_space>();

namespace cs_impl {
	template<>
	cs::namespace_t &get_ext<cs_impl::sqlite>()
	{
		return sqlite_db_ext;
	}

	template<>
	cs::namespace_t &get_ext<cs_impl::sqlite::statement>()
	{
		return sqlite_stmt_ext;
	}

	template<>
	constexpr const char *get_name_of_type<cs_impl::sqlite>()
	{
		return "cs::sqlite";
	}

	template<>
	constexpr const char *get_name_of_type<cs_impl::sqlite::data_type>()
	{
		return "cs::sqlite::data_type";
	}

	template<>
	constexpr const char *get_name_of_type<cs_impl::sqlite::statement>()
	{
		return "cs::sqlite::statement";
	}
}
namespace sqlite_cs_ext {
	using namespace cs;
	using cs_impl::sqlite;

// Sqlite Statement
	bool done(const sqlite::statement &stmt)
	{
		return stmt.done();
	}

	void reset(sqlite::statement &stmt)
	{
		stmt.reset();
	}

	void exec(sqlite::statement &stmt)
	{
		stmt.step();
	}

	number column_count(const sqlite::statement &stmt)
	{
		return stmt.column_count();
	}

	sqlite::data_type column_type(const sqlite::statement &stmt, number index)
	{
		return stmt.column_type(index);
	}

	string column_name(const sqlite::statement &stmt, number index)
	{
		return stmt.column_name(index);
	}

	string column_decltype(const sqlite::statement &stmt, number index)
	{
		return stmt.column_decltype(index);
	}

	number column_integer(const sqlite::statement &stmt, number index)
	{
		return stmt.column_integer(index);
	}

	number column_real(const sqlite::statement &stmt, number index)
	{
		return stmt.column_real(index);
	}

	string column_text(const sqlite::statement &stmt, number index)
	{
		return stmt.column_text(index);
	}

	number bind_param_count(const sqlite::statement &stmt)
	{
		return stmt.bind_param_count();
	}

	void bind_integer(sqlite::statement &stmt, number index, number data)
	{
		stmt.bind_integer(index, data);
	}

	void bind_real(sqlite::statement &stmt, number index, number data)
	{
		stmt.bind_real(index, data);
	}

	void bind_text(sqlite::statement &stmt, number index, const string &data)
	{
		stmt.bind_text(index, data);
	}

	void clear_bindings(sqlite::statement &stmt)
	{
		stmt.clear_bindings();
	}

// Sqlite
	sqlite open(const string &path)
	{
		return sqlite(path);
	}

	sqlite::statement prepare(sqlite &db, const string &sql)
	{
		return db.prepare(sql);
	}

	void init(name_space* ns)
	{
		(*ns)
		.add_var("db", make_namespace(sqlite_db_ext))
		.add_var("statement", make_namespace(sqlite_stmt_ext))
		.add_var("integer", var::make_constant<sqlite::data_type>(sqlite::data_type::integer))
		.add_var("real", var::make_constant<sqlite::data_type>(sqlite::data_type::real))
		.add_var("text", var::make_constant<sqlite::data_type>(sqlite::data_type::text))
		.add_var("open", make_cni(open))
		.add_var("prepare", make_cni(prepare));
		(*sqlite_db_ext)
		.add_var("integer", var::make_constant<sqlite::data_type>(sqlite::data_type::integer))
		.add_var("real", var::make_constant<sqlite::data_type>(sqlite::data_type::real))
		.add_var("text", var::make_constant<sqlite::data_type>(sqlite::data_type::text))
		.add_var("prepare", make_cni(prepare));
		(*sqlite_stmt_ext)
		.add_var("done", make_cni(done))
		.add_var("reset", make_cni(reset))
		.add_var("exec", make_cni(exec))
		.add_var("column_count", make_cni(column_count))
		.add_var("column_type", make_cni(column_type))
		.add_var("column_name", make_cni(column_name))
		.add_var("column_decltype", make_cni(column_decltype))
		.add_var("column_integer", make_cni(column_integer))
		.add_var("column_real", make_cni(column_real))
		.add_var("column_text", make_cni(column_text))
		.add_var("bind_param_count", make_cni(bind_param_count))
		.add_var("bind_integer", make_cni(bind_integer))
		.add_var("bind_real", make_cni(bind_real))
		.add_var("bind_text", make_cni(bind_text))
		.add_var("clear_bindings", make_cni(clear_bindings));
	}
}

void cs_extension_main(cs::name_space* ns)
{
	sqlite_cs_ext::init(ns);
}