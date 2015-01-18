<?php
namespace m5D02F22739AA11E4B3C6005056847E34\exceptions;

\m5D02F22739AA11E4B3C6005056847E34\applicationFrameworkClass::classLoader('exceptionClass', 'exceptions');
class constantNotExistsExceptionClass extends exceptionClass
{
	use \m5D02F22739AA11E4B3C6005056847E34\traits\propertysClass;

	private static $_staticParams = [];
	private $_instanceParams = [
		'propertys' => [
			'className' => [
				'set' => false,
			],
			'constant' => [
				'set' => false,
			]
		]
	];
	
	public function __construct ($className, $constant)
	{
		$this->propertySet('className', $className);
		$this->propertySet('constant', $constant);
		parent::__construct("類別 [{$className}] 中未宣告指定的常數 [{$constant}]");
	}
}