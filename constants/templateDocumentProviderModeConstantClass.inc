<?php
/**
	套版種類常數類別
*/
namespace m5D02F22739AA11E4B3C6005056847E34\constants;
\m5D02F22739AA11E4B3C6005056847E34\applicationFrameworkClass::classLoader('constantCheckerClass', 'traits');

/**
	套版種類常數類別
*/
class templateDocumentProviderModeConstantClass {
	use \m5D02F22739AA11E4B3C6005056847E34\traits\constantCheckerClass;
	const MODE_BLOCK = 'block';	
	const MODE_LABEL = 'label';	
	private static $_staticParams = [
		'modeList' => [
			self::MODE_BLOCK => '',
			self::MODE_LABEL => '',
		]
	];
	private $_instanceParams = [];
	
	public static function modeListChecker($constantName)
	{
		static::constantChecker('modeList', $constantName);
	}
}