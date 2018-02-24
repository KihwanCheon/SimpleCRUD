//
// Created by NHNEnt on 2018. 2. 17..
//
#pragma once

#include <string>
#include <sqlite3.h>
#include "SqlTemplate.h"

namespace Member {

	struct Member
	{
		int id;
		std::string name;
		int age;
	};

	class DAO :private SqlTemplate {
	public:
		explicit DAO(sqlite3* &conn);

		~DAO();

	private:
	public:
		bool insert(Member &dto);

		bool select(const char* name, Member &dto);

		bool count(int &count);
	};
}
