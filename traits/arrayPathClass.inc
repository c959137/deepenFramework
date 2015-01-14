<?php
namespace m5D02F22739AA11E4B3C6005056847E34\traits;
trait arrayPathClass 
{
	protected static function arrayToPath()
	{
		$list = [];
		$args = func_get_args();
		foreach ($args as $arg) {
			if (is_array($arg)) {
					$list = array_merge($list, $arg);
			} else {
				$list = array_merge($list, explode(DIRECTORY_SEPARATOR, $arg));
			};
		}
		$fullPath = '';
		foreach ($list as $path) {
			if (!$path) {
				continue;
			}
			if ($fullPath != '') $fullPath .= DIRECTORY_SEPARATOR; 
			$fullPath .= $path;
		}
		$fullPath = DIRECTORY_SEPARATOR . $fullPath;
		return $fullPath;
	}
	
	protected static function pathToArray($path)
	{
		var_dump (explode('\\', $path));
		xxx();
	}
	
	protected static function classInfo($fullClassName)
	{
		$info = explode('\\', $fullClassName);
		$list = [];
		$list['className'] = array_pop($info);
		if (!empty($info)) {
			$list['namespace'] = '';
			foreach ($info as $path) {
				if ($list['namespace'] != '') {
					$list['namespace'] .= '\\';
				}
				$list['namespace'] .= $path;
			}
		}
		return $list;
	}
	
	protected static function nsJoin($nsLeft, $nsRight)
	{
		$ns = '';
		$info = array_merge(explode('\\', $nsLeft), explode('\\', $nsRight));
		foreach ($info as $path) {
			if (!$path) {
				continue;
			}
			if ($ns != '') {
				$ns .= '\\';
			}
			$ns .= $path;
		}
		return $ns;
	}
	
	protected static function nsToPath($rootPath, $ns)
	{
		$info = explode('\\', $ns);
		$rightPath = '';
		foreach ($info as $path) {
			if (!$path) {
				continue;
			}
			if ($rightPath != '') {
				$rightPath .= DIRECTORY_SEPARATOR;
			}
			$rightPath .= $path;
		}
		if ($rightPath) {
			$rootPath .= DIRECTORY_SEPARATOR . $rightPath;
		}
		return $rootPath;
	}
}