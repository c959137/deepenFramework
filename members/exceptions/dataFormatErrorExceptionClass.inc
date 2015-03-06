<?php
namespace m5D02F22739AA11E4B3C6005056847E34\members\exceptions;
\m5D02F22739AA11E4B3C6005056847E34\applicationFrameworkClass::classLoader('memberExceptionClass', 'members\exceptions');
class dataFormatErrorExceptionClass extends memberExceptionClass
{
	use \m5D02F22739AA11E4B3C6005056847E34\traits\propertysClass;
	private $_instanceParams = [
		'propertys' => [
			'propName' => [
				'get' => true,
				'set' => false,
			],
			'oldValue' => [
				'get' => true,
				'set' => false,
			]
		]
	];

	public function __construct($propName, $oldValue, $message = '資料格式錯誤')
	{
		$this->propertySet('propName', $propName);
		$this->propertySet('oldValue', $oldValue);
		parent::__construct($message);
	}
}
