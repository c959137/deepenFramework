<?php
namespace m5D02F22739AA11E4B3C6005056847E34\traits;
trait fileUtilsClass 
{
	protected static function pathChecker($path, $createDir = false)
	{
		if (file_exists($path)) {
			return true;
		}
		if (!$createDir) {
			return false;
		}
		
		$umask = umask(0002);
		$flag = mkdir($path, 0775, true);
		umask($umask);
		/*
		0664 => drw-r--r--
		0774 => drwxr-xr--
		*/
		return $flag;
	}
}