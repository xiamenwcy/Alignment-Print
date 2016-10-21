/*************************************************
2 * Copyright (c) 2016.10.14-2020.10.01
3 * All rights reserved.
4 *
5 * 文件名称： AlignmentPrint.h
6 * 摘要： 本文件用于格式化输出表格，包含输出到控制台和文件中。
7 *
8 *
9 * 本项目参考了网上的解答：http://stackoverflow.com/questions/14765155/how-can-i-easily-format-my-data-table-in-c
10*
11 * 当前版本：v1.0
12 * 作者：北雁
13 * 完成日期：2016年10月14日
14 *
15 */

#ifndef  ALIGNMENTPRINT_H_
#define  ALIGNMENTPRINT_H_

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

namespace AlignmentTable
{
	/**
	* \brief 对齐方式
	*/
	typedef enum
	{
		LEFT,    /**< 左对齐*/
		RIGHT,   /**< 右对齐*/
		CENTER   /**< 中间对齐*/
	}ALIGNMENT;
	typedef enum
	{
		APPEND,  /**< 所有输出附加在文件末尾，即使定位指针也是附加在文件末尾。 */
		TRUNCATE /**< 如果文件已存在则先删除该文件*/
	}MODE;


	/**
	* \brief 用于格式化输出表格到控制台。
	*
	*/
	class TableFormatC
	{
	public:
		TableFormatC() : m_width(10), m_fill(" "), m_alignment(CENTER)
		{

		}
		TableFormatC(int width, std::string fill, ALIGNMENT alignment) :m_width(width), m_fill(fill), m_alignment(alignment)
		{

		}
		~TableFormatC()
		{
		}
		/**
		* \brief Right-aligns string within a field of width w. Pads with blank spaces
		* to enforce alignment.
		*/
		template<typename T>
		std::string right(const T&  s, const int w)
		{
			std::stringstream ss, spaces;
			std::string convert_str;
			ss << s;
			getline(ss, convert_str); //convert_str=ss.str(); 
			int padding = w - convert_str.size();                 // count excess room to pad
			for (int i = 0; i < padding; ++i)
				spaces << m_fill;
			//必须牢记使用stringstream两次输入，必须使用前清空
			ss.clear();
			ss.str("");
			ss << spaces.str() << convert_str;                    // format with padding
			return ss.str();
		}



		/**
		* \brief Left-aligns string within a field of width w. Pads with blank spaces
		* to enforce alignment.
		*/
		template<typename T>
		std::string left(const T& s, const int w)
		{
			std::stringstream ss, spaces;
			std::string convert_str;
			ss << s;
			getline(ss, convert_str); //convert_str=ss.str(); 
			int padding = w - convert_str.size();                 // count excess room to pad
			for (int i = 0; i < padding; ++i)
				spaces << m_fill;
			//必须牢记使用stringstream两次输入，必须使用前清空
			ss.clear();
			ss.str("");
			ss << convert_str << spaces.str();                    // format with padding
			return ss.str();
		}

		/**
		* \brief Center-aligns string within a field of width w. Pads with blank spaces
		* to enforce alignment.
		*/
		template<typename T>
		std::string center(const T& s, const int w)
		{
			std::stringstream ss, spaces;
			std::string convert_str;
			ss << s;
			//ss >> std::ws;//加上这句，就会跳过开始的空格," abs"读出为"abs",对getline起作用，对ss.str()不起作用
			getline(ss, convert_str); //防止空格被跳过，例如“hello world”被输出成"hello"
			//convert_str=ss.str();  //这个也可以
			int padding = w - convert_str.size();                 // count excess room to pad
			for (int i = 0; i<padding / 2; ++i)
				spaces << m_fill;
			//必须牢记使用stringstream两次输入，必须使用前清空
			ss.clear();
			ss.str("");
			ss << spaces.str() << convert_str << spaces.str();    // format with padding
			if (padding>0 && padding % 2 != 0)               // if odd #, add 1 space
				ss << m_fill;
			return ss.str();
		}

		template<typename T>
		TableFormatC& operator<<(const T& data)
		{
			std::string result;
			switch (m_alignment)
			{
			case LEFT:
			{
						 std::cout << left(data, m_width);
			} break;
			case RIGHT:
			{
						  std::cout << right(data, m_width);
			} break;
			default: //CENTER
			{
						 std::cout << center(data, m_width);
			}break;
			}
			return *this;
		}
		TableFormatC& operator<<(std::ostream&(*out)(std::ostream&))
		{
			std::cout << out;
			return *this;
		}
	private:
		int m_width;                 /**< 控制每个数值的长度 */
		std::string m_fill;           /**< 填充空白*/
		ALIGNMENT m_alignment;        /**<  对齐方式*/
	};

	/**
	* \brief 用于格式化输出表格到文件
	*
	* 格式化输出参考：[C++ - 文件读写操作(fstream)](http://blog.163.com/dingmz_frcmyblog/blog/static/21730402320133174330716/)
	*/
	class TableFormatF
	{
	public:
		TableFormatF(std::string  file,MODE mode=TRUNCATE) : m_width(10), m_fill(" "), m_alignment(CENTER), m_file(file)
		{
			if (mode==TRUNCATE)
			{
				os.open(m_file); //默认打开方式：	ios::out | ios::trunc
			}
			else
			{
				os.open(m_file, std::ios::app);
			}
		
			if (!os)
			{
				std::cout << "Create file failure...\n";
				exit(0);
			}
		}
		TableFormatF(int width, std::string fill, ALIGNMENT alignment, std::string  file, MODE mode = TRUNCATE) :m_width(width), m_fill(fill), m_alignment(alignment), m_file(file)
		{
			if (mode == TRUNCATE)
			{
				os.open(m_file); //默认打开方式：	ios::out | ios::trunc
			}
			else
			{
				os.open(m_file, std::ios::app);
			}
			if (!os)
			{
				std::cout << "Create file failure...\n";
				exit(0);
			}
		}
		~TableFormatF()
		{
			if (os.is_open())
			{
				os.close();
			}
		}
		/**
		* \brief Right-aligns string within a field of width w. Pads with blank spaces
		* to enforce alignment.
		*/
		template<typename T>
		std::string right(const T&  s, const int w)
		{
			std::stringstream ss, spaces;
			std::string convert_str;
			ss << s;
			getline(ss, convert_str); //convert_str=ss.str(); 
			int padding = w - convert_str.size();                 // count excess room to pad
			for (int i = 0; i < padding; ++i)
				spaces << m_fill;
			//必须牢记使用stringstream两次输入，必须使用前清空
			ss.clear();
			ss.str("");
			ss << spaces.str() << convert_str;                    // format with padding
			return ss.str();
		}



		/**
		* \brief Left-aligns string within a field of width w. Pads with blank spaces
		* to enforce alignment.
		*/
		template<typename T>
		std::string left(const T& s, const int w)
		{
			std::stringstream ss, spaces;
			std::string convert_str;
			ss << s;
			getline(ss, convert_str); //convert_str=ss.str(); 
			int padding = w - convert_str.size();                 // count excess room to pad
			for (int i = 0; i < padding; ++i)
				spaces << m_fill;
			//必须牢记使用stringstream两次输入，必须使用前清空
			ss.clear();
			ss.str("");
			ss << convert_str << spaces.str();                    // format with padding
			return ss.str();
		}
		/**
		* \brief Center-aligns string within a field of width w. Pads with blank spaces
		* to enforce alignment.
		*/
		template<typename T>
		std::string center(const T& s, const int w)
		{
			std::stringstream ss, spaces;
			std::string convert_str;
			ss << s;
			getline(ss, convert_str); //convert_str=ss.str(); 
			int padding = w - convert_str.size();                 // count excess room to pad
			for (int i = 0; i<padding / 2; ++i)
				spaces << m_fill;
			//必须牢记使用stringstream两次输入，必须使用前清空
			ss.clear();
			ss.str("");
			ss << spaces.str() << convert_str << spaces.str();    // format with padding
			if (padding>0 && padding % 2 != 0)               // if odd #, add 1 space
				ss << m_fill;
			return ss.str();
		}
		template<typename T>
		TableFormatF& operator<<(const T& data)
		{
			std::string result;
			switch (m_alignment)
			{
			case LEFT:
			{
						 os << left(data, m_width);
			} break;
			case RIGHT:
			{
						  os << right(data, m_width);
			} break;
			default:
			{
					   os << center(data, m_width);
			}break;
			}
			return *this;
		}
		/**
		* \brief 用于连续输出
		*
		*/
		TableFormatF& operator<<(std::ostream&(*out)(std::ostream&))
		{
			os << out;
			return *this;
		}
	private:
		int m_width;                  /**< 控制每个数值的长度 */
		std::string m_fill;           /**< 填充空白*/
		ALIGNMENT m_alignment;        /**<  对齐方式*/
		std::string m_file;           /**<  输出文件     */
		std::ofstream  os;            /**<   输出流      */
	};
}
#endif