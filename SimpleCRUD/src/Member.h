//
// Created by NHNEnt on 2018. 2. 17..
//
#pragma once

#include <string>
#include <sqlite3.h>
#include "SqlTemplate.h"

namespace Member {

	class DAO;

	class Member
	{
	public:
		explicit Member(DAO& dao);;
		~Member();

	private:
		Member(const Member&);
		Member& operator=(const Member&);

	private:
		DAO &dao;

	public:
		int id;
		std::string name;
		int age;
	public:
		void save();
		void refresh();
	};

	class DAO :public SqlTemplate 
	{
	public:
		explicit DAO(sqlite3* &conn);
		virtual ~DAO();

	private:
		DAO(const DAO&);
		DAO& operator=(const DAO&);
	
	public:
		bool insert(Member &dto);

		bool update(Member &dto);

		bool select(const char* name, Member &dto);

		bool count(int &count);

		int selectById(Member &dto);
	};
}
