<?php
/*
	網頁資源常數
*/
namespace m5D02F22739AA11E4B3C6005056847E34\constants;

/*
	資源常數類別
*/
class httpContentTypeConstantClass {
	use \m5D02F22739AA11E4B3C6005056847E34\traits\constantCheckerClass;
	
	const CONTENT_TYPE_LIST = 'contentTypeList';
	
	const CT_JSON = 'json';
	const CT_JS = 'js';
	const CT_HTML = 'html';
	const CT_XML = 'xml';
	
	private static $_staticParams = [
		self::CONTENT_TYPE_LIST => [
			self::CT_JSON   => 'application/json; charset=UTF-8',
			self::CT_JS 	  => 'text/javascript; charset=UTF-8',
			self::CT_HTML   => 'text/html; charset=utf-8',
      self::CT_XML    => 'text/xml; charset=utf-8',
		]
	];
	
	private $_instanceParams = [];
	
	public static function contentTypeChecker($constantName)
	{
		static::constantChecker(self::CONTENT_TYPE_LIST, $constantName);
		return $constantName;
	}
	
	public static function contentTypeHeader($constantName)
	{
		return self::$_staticParams[self::CONTENT_TYPE_LIST][$constantName];
	}
}