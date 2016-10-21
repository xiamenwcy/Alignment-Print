/*************************************************
2 * Copyright (c) 2016.10.14-2020.10.01
3 * All rights reserved.
4 *
5 * �ļ����ƣ� AlignmentPrint.h
6 * ժҪ�� ���ļ����ڸ�ʽ�������񣬰������������̨���ļ��С�
7 *
8 *
9 * ����Ŀ�ο������ϵĽ��http://stackoverflow.com/questions/14765155/how-can-i-easily-format-my-data-table-in-c
10*
11 * ��ǰ�汾��v1.0
12 * ���ߣ�����
13 * ������ڣ�2016��10��14��
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
	* \brief ���뷽ʽ
	*/
	typedef enum
	{
		LEFT,    /**< �����*/
		RIGHT,   /**< �Ҷ���*/
		CENTER   /**< �м����*/
	}ALIGNMENT;
	typedef enum
	{
		APPEND,  /**< ��������������ļ�ĩβ����ʹ��λָ��Ҳ�Ǹ������ļ�ĩβ�� */
		TRUNCATE /**< ����ļ��Ѵ�������ɾ�����ļ�*/
	}MODE;


	/**
	* \brief ���ڸ�ʽ�������񵽿���̨��
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
			//�����μ�ʹ��stringstream�������룬����ʹ��ǰ���
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
			//�����μ�ʹ��stringstream�������룬����ʹ��ǰ���
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
			//ss >> std::ws;//������䣬�ͻ�������ʼ�Ŀո�," abs"����Ϊ"abs",��getline�����ã���ss.str()��������
			getline(ss, convert_str); //��ֹ�ո����������硰hello world���������"hello"
			//convert_str=ss.str();  //���Ҳ����
			int padding = w - convert_str.size();                 // count excess room to pad
			for (int i = 0; i<padding / 2; ++i)
				spaces << m_fill;
			//�����μ�ʹ��stringstream�������룬����ʹ��ǰ���
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
		int m_width;                 /**< ����ÿ����ֵ�ĳ��� */
		std::string m_fill;           /**< ���հ�*/
		ALIGNMENT m_alignment;        /**<  ���뷽ʽ*/
	};

	/**
	* \brief ���ڸ�ʽ���������ļ�
	*
	* ��ʽ������ο���[C++ - �ļ���д����(fstream)](http://blog.163.com/dingmz_frcmyblog/blog/static/21730402320133174330716/)
	*/
	class TableFormatF
	{
	public:
		TableFormatF(std::string  file,MODE mode=TRUNCATE) : m_width(10), m_fill(" "), m_alignment(CENTER), m_file(file)
		{
			if (mode==TRUNCATE)
			{
				os.open(m_file); //Ĭ�ϴ򿪷�ʽ��	ios::out | ios::trunc
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
				os.open(m_file); //Ĭ�ϴ򿪷�ʽ��	ios::out | ios::trunc
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
			//�����μ�ʹ��stringstream�������룬����ʹ��ǰ���
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
			//�����μ�ʹ��stringstream�������룬����ʹ��ǰ���
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
			//�����μ�ʹ��stringstream�������룬����ʹ��ǰ���
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
		* \brief �����������
		*
		*/
		TableFormatF& operator<<(std::ostream&(*out)(std::ostream&))
		{
			os << out;
			return *this;
		}
	private:
		int m_width;                  /**< ����ÿ����ֵ�ĳ��� */
		std::string m_fill;           /**< ���հ�*/
		ALIGNMENT m_alignment;        /**<  ���뷽ʽ*/
		std::string m_file;           /**<  ����ļ�     */
		std::ofstream  os;            /**<   �����      */
	};
}
#endif