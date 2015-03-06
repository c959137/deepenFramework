<?php
namespace m5D02F22739AA11E4B3C6005056847E34\members\exceptions;
\m5D02F22739AA11E4B3C6005056847E34\applicationFrameworkClass::classLoader('memberExceptionClass', 'members\exceptions');
class accountIdExistsExceptionClass extends memberExceptionClass
{
	use \m5D02F22739AA11E4B3C6005056847E34\traits\propertysClass;
	private $_instanceParams = [
		'propertys' => [
			'propName' => [
				'get' => true,
				'set' => false,
			],
		]
	];

	public function __construct($propName)
	{
		$this->propertySet('propName', $propName);
		parent::__construct('申請的帳號已經被人使用');
	}
}
