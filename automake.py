#!/usr/bin/python
#	coding: UTF-8
#	author:	XuZhiXi
#	create Time: 2012-08-02 18:15:39

import os
import re
from automake_config import *


# program global set
COMMON_TYPE = 1		# common program
DYNAMIC_TYPE = 2	# dynamic library
STATIC_TYPE = 3		# static library

g_tabKey = "\t"
g_newLine = g_tabKey
g_mid_ext = ".o"			# 中间文件扩展名
g_debug_mid_ext = ".od"		# debug中间文件扩展名

includeReg = ur'''^\s*#include\s*<(ky.+?\.h)>\s*$'''		# 获取所包含头文件的正则表达式
sourceItemList = None
headerItemList = None


def get_depandent_str(fileName, suffix) :
	resultList = []
	get_depandent_list( fileName, resultList )
	resultList = list( set( resultList ) )	# 去重

	return get_str_by_filelist( resultList, suffix ) 

def get_str_by_filelist(fileNameList, suffix = ".h") :
	depandentStr = ""
	for fileName in fileNameList :
		basename = os.path.splitext( os.path.basename( fileName ) )[0]
		if basename in headerItemList :
			depandentStr += ("\\\n" + g_tabKey + headerItemList[basename])

	return depandentStr

def get_depandent_list(fileName, depandentList) :
	basedir = os.path.dirname( fileName )
	f = open( fileName, "r" )
	reObj = re.compile( includeReg )
	for line in f :
		fileNameList = reObj.findall( line )
		if fileNameList :
			fullName = os.path.abspath( os.path.join( basedir, fileNameList[0] ) )
			if (fullName not in depandentList) and os.path.exists(fullName) :
				depandentList.append( fullName )
				get_depandent_list( fullName, depandentList )

def is_same_dir(srcDir, dstDir) :
	'''
	是否同一目录
	'''
	
	if os.path.abspath(srcDir) == os.path.abspath(dstDir) :
		return True
	else :
		return False

def get_files(path, typeList, isRecursion = False, exceptFileList = [], exceptDirList = []) :
	'''
	description: 获取符合条件的文件名(包括路径)列表
	param path 指定路径
	param typeList 文件类型
	param isRecursion 是否递归处理子目录
	param exceptFileList 除外的文件
	param exceptDirList 除外的目录,仅当isRecursion为True时才生效
	'''

	resultList = []
	fileNames = os.listdir(path)
	for name in fileNames :
		filePath = os.path.join(path, name)
		fileFullPath = os.path.abspath(filePath)
		isDir = os.path.isdir(filePath)
		if isDir and (isRecursion == True) and (fileFullPath not in exceptDirList) :
			resultList.extend( get_files(filePath, typeList, isRecursion, exceptFileList, exceptDirList) )	# 处理子目录
		elif not isDir and (os.path.splitext(filePath)[1] in typeList) and (fileFullPath not in exceptFileList) :
			resultList.append(filePath)		# 处理文件

	return resultList

def createIndex(fileList) :
	'''
	建立索引
	'''

	resultDict = {}
	for filePath in fileList :
		fileName = os.path.split(filePath)[1]
		fileName = os.path.splitext(fileName)[0]
		resultDict[fileName] = filePath

	return resultDict

def print_compilers() :
	print "################################################################################"
	print "### Compilers ##################################################################"
	print "################################################################################"
	print g_newLine

	print "INCLUDEPATH=" + g_include_opt
	print "LIBS=" + g_libs_opt
	print g_newLine

	print "CC=gcc -c $(INCLUDEPATH) " + g_compilers_opt + " -o"
	print "CC_DEBUG=gcc -g -c $(INCLUDEPATH) " + g_debug_compilers_opt + " -o"
	print "CC_LINKER=gcc $(INCLUDEPATH) " + g_compilers_opt + " -o"
	print "CC_LINKER_DEBUG=gcc -g $(INCLUDEPATH) " + g_debug_compilers_opt + " -o"
	print g_newLine

	print "CPP=g++ -c $(INCLUDEPATH) " + g_compilers_opt + " -o"
	print "CPP_DEBUG=g++ -g -c $(INCLUDEPATH) " + g_debug_compilers_opt + " -o"
	print "CPP_LINKER=g++ $(INCLUDEPATH) " + g_compilers_opt + " -o"
	print "CPP_LINKER_DEBUG=g++ -g $(INCLUDEPATH) " + g_debug_compilers_opt + " -o"
	print g_newLine

	print "AR=ar " + g_ar_opt + " cqs"
	print "AR_DEBUG=ar " + g_ar_opt + " cqs"
	print g_newLine

def print_objects(sourceItemList) :
	print "################################################################################"
	print "### Generated object files #####################################################"
	print "################################################################################"
	print g_newLine

	objFileListStr = ""
	objDebugFileListStr = ""
	for name in sourceItemList :
		objFileListStr += ( g_tabKey + name + g_mid_ext + "\\\n" )
		objDebugFileListStr += ( g_tabKey + name + g_debug_mid_ext + "\\\n")
	print "OBJECTS=\\"
	print objFileListStr + g_tabKey
	print "OBJECTS_DEBUG=\\"
	print objDebugFileListStr + g_tabKey

def print_project_file(sourceItemList):
	print "################################################################################"
	print "### Project Files ##############################################################"
	print "################################################################################"
	print g_newLine

	print "all: $(OBJECTS)"
	if g_program_type == STATIC_TYPE :
		printTab( "%s$(AR) %s $(OBJECTS)", g_bin_name )
	else :
		printTab( "$(CPP_LINKER) %s $(OBJECTS) $(LIBS)", g_bin_name )
	for name in sourceItemList :
		print "%s%s: %s%s" % ( name, g_mid_ext, sourceItemList[name], get_depandent_str(sourceItemList[name], ".h") )
		if os.path.splitext( sourceItemList[name] )[1] == ".c" :
			printTab( "$(CC) %s%s %s", name, g_mid_ext, sourceItemList[name] )
		else :
			printTab( "$(CPP) %s%s %s", name, g_mid_ext, sourceItemList[name] )
	print g_newLine

	print "debug: $(OBJECTS_DEBUG)"
	if g_program_type == STATIC_TYPE :
		printTab( "$(AR_DEBUG) %s $(OBJECTS_DEBUG)", g_debug_bin_name)
	else :
		printTab( "$(CPP_LINKER_DEBUG) %s $(OBJECTS_DEBUG) $(LIBS)", g_debug_bin_name )
	for name in sourceItemList :
		print "%s%s: %s%s" % ( name, g_debug_mid_ext, sourceItemList[name], get_depandent_str(sourceItemList[name], ".h") )
		if os.path.splitext( sourceItemList[name] )[1] == ".c" :
			printTab( "$(CC_DEBUG) %s%s %s", name, g_debug_mid_ext, sourceItemList[name] )	
		else :
			printTab( "$(CPP_DEBUG) %s%s %s", name, g_debug_mid_ext, sourceItemList[name] )	
	print g_newLine
	
	print "install:"
	for command in g_install_commands :
		printTab( command )
	print g_newLine

	print "clean:"
	printTab( "rm -f %s %s", g_bin_name, g_debug_bin_name )
	printTab( "rm -rf *%s *%s", g_mid_ext, g_debug_mid_ext )

def printTab(format, *args) :
	print g_tabKey,
	print format % args


if __name__ == "__main__" :
	path = "."
	sourceTypeList = (".cpp", ".c")
	headerTypeList = (".h", )
	exceptFileList = [ os.path.abspath(i) for i in g_except_file_list ]
	exceptDirList  = [ os.path.abspath(i) for i in g_except_dir_list ]
	sourceItemList = createIndex( get_files(path, sourceTypeList, g_handle_subdir, exceptFileList, exceptDirList) )
	headerItemList = createIndex( get_files(path, headerTypeList, g_handle_subdir, exceptFileList, exceptDirList) )

	if g_program_type == DYNAMIC_TYPE :
		g_libs_opt += " -shared"

	print_compilers()
	print_objects(sourceItemList)
	print_project_file(sourceItemList)
	
