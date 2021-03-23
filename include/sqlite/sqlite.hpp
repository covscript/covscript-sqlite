#pragma once
/*
* Covariant Script Sqlite
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
* Copyright (C) 2017-2021 Michael Lee(李登淳)
*
* Email:   lee@covariant.cn, mikecovlee@163.com
* Github:  https://github.com/mikecovlee
* Website: http://covscript.org.cn
*/
#include "sqlite3.h"
#include <utility>
#include <string>
#include <memory>
#include <covscript/dll.hpp>

namespace cs_impl {
	class sqlite final {
		class db_holder final {
		public:
			::sqlite3 *db;

			db_holder()
			{
				if (::sqlite3_open(":memory:", &db) != SQLITE_OK)
					throw cs::lang_error(::sqlite3_errmsg(db));
			}

			explicit db_holder(const char *path)
			{
				if (::sqlite3_open(path, &db) != SQLITE_OK)
					throw cs::lang_error(::sqlite3_errmsg(db));
			}

			db_holder(const db_holder &) = delete;

			~db_holder()
			{
				::sqlite3_close(db);
			}
		};

		class stmt_holder final {
		public:
			int errcode = SQLITE_OK;

			::sqlite3 *host;

			::sqlite3_stmt *stmt;

			stmt_holder() = delete;

			explicit stmt_holder(::sqlite3 *db, const char *sql, std::size_t len) : host(db)
			{
				if (::sqlite3_prepare_v2(host, sql, len, &stmt, nullptr) != SQLITE_OK)
					throw cs::lang_error(::sqlite3_errmsg(db));
			}

			stmt_holder(const stmt_holder &) = delete;

			~stmt_holder()
			{
				::sqlite3_finalize(stmt);
			}
		};

		std::shared_ptr <db_holder> m_db;
	public:
		enum class data_type {
			integer, real, text
		};

		class statement final {
			friend class sqlite;

			std::shared_ptr <stmt_holder> m_stmt;

			explicit statement(const std::shared_ptr <db_holder> &db, const std::string &sql) : m_stmt(
				    std::make_shared<stmt_holder>(db->db, sql.c_str(), sql.size())) {}

		public:
			statement() = delete;

			statement(const statement &) = default;

			~statement() = default;

			bool done() const
			{
				return m_stmt->errcode == SQLITE_DONE;
			}

			void reset()
			{
				if (::sqlite3_reset(m_stmt->stmt) != SQLITE_OK)
					throw cs::lang_error(::sqlite3_errmsg(m_stmt->host));
			}

			void step()
			{
				if ((m_stmt->errcode = ::sqlite3_step(m_stmt->stmt)) == SQLITE_ERROR)
					throw cs::lang_error(::sqlite3_errmsg(m_stmt->host));
			}

			std::size_t column_count() const
			{
				return ::sqlite3_column_count(m_stmt->stmt);
			}

			data_type column_type(std::size_t index) const
			{
				switch (::sqlite3_column_type(m_stmt->stmt, index)) {
				case SQLITE_INTEGER:
					return data_type::integer;
				case SQLITE_FLOAT:
					return data_type::real;
				case SQLITE_TEXT:
					return data_type::text;
				default:
					throw cs::lang_error("Unsupported type.");
				}
			}

			std::string column_name(std::size_t index) const
			{
				return ::sqlite3_column_name(m_stmt->stmt, index);
			}

			std::string column_decltype(std::size_t index) const
			{
				return ::sqlite3_column_decltype(m_stmt->stmt, index);
			}

			int column_integer(std::size_t index) const
			{
				return ::sqlite3_column_int(m_stmt->stmt, index);
			}

			double column_real(std::size_t index) const
			{
				return ::sqlite3_column_double(m_stmt->stmt, index);
			}

			std::string column_text(std::size_t index) const
			{
				return reinterpret_cast<const char *>(::sqlite3_column_text(m_stmt->stmt, index));
			}

			std::size_t bind_param_count() const
			{
				return ::sqlite3_bind_parameter_count(m_stmt->stmt);
			}

			void bind_integer(std::size_t index, int data)
			{
				if (::sqlite3_bind_int(m_stmt->stmt, index, data) != SQLITE_OK)
					throw cs::lang_error(::sqlite3_errmsg(m_stmt->host));
			}

			void bind_real(std::size_t index, double data)
			{
				if (::sqlite3_bind_double(m_stmt->stmt, index, data) != SQLITE_OK)
					throw cs::lang_error(::sqlite3_errmsg(m_stmt->host));
			}

			void bind_text(std::size_t index, const std::string &data)
			{
				if (::sqlite3_bind_text(m_stmt->stmt, index, data.c_str(), data.size(), nullptr) != SQLITE_OK)
					throw cs::lang_error(::sqlite3_errmsg(m_stmt->host));
			}

			void clear_bindings()
			{
				::sqlite3_clear_bindings(m_stmt->stmt);
			}
		};

		sqlite() : m_db(std::make_shared<db_holder>()) {}

		explicit sqlite(const std::string &path) : m_db(std::make_shared<db_holder>(path.c_str())) {}

		sqlite(const sqlite &) = default;

		~sqlite() = default;

		statement prepare(const std::string &sql)
		{
			return statement(m_db, sql);
		}
	};
}
