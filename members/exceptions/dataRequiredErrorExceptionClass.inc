<?php
namespace m5D02F22739AA11E4B3C6005056847E34\members\exceptions;
\m5D02F22739AA11E4B3C6005056847E34\applicationFrameworkClass::classLoader('memberExceptionClass', 'members\exceptions');
class dataRequiredErrorExceptionClass extends memberExceptionClass
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

	public function __construct($propName, $message = '這是必要欄位')
	{
		$this->propertySet('propName', $propName);
		parent::__construct($message);
	}
}