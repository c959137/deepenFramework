<?php
/*
	網頁資源常數
*/
namespace m5D02F22739AA11E4B3C6005056847E34\constants;
\m5D02F22739AA11E4B3C6005056847E34\applicationFrameworkClass::classLoader('constantCheckerClass', 'traits');
/*
	資源常數類別
*/
class resourceTypeConstantClass {
	use \m5D02F22739AA11E4B3C6005056847E34\traits\constantCheckerClass;
	const RESOURCE_TYPE_CSS = 'css';	
	const RESOURCE_TYPE_JS = 'js';
	private static $_staticParams = [
		'resourceTypeList' => [
			self::RESOURCE_TYPE_CSS => '',
			self::RESOURCE_TYPE_JS => '',
		]
	];
	private $_instanceParams = [];
	
	public static function resourceTypeChecker($constantName)
	{
		static::constantChecker('resourceTypeList', $constantName);
	}
}