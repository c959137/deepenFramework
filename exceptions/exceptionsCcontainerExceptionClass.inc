<?php
namespace m5D02F22739AA11E4B3C6005056847E34\exceptions;

\m5D02F22739AA11E4B3C6005056847E34\applicationFrameworkClass::classLoader('exceptionClass', 'exceptions');
class exceptionsCcontainerExceptionClass extends exceptionClass
{
	use \m5D02F22739AA11E4B3C6005056847E34\traits\propertysClass;

	private static $_staticParams = [];
	private $_instanceParams = [
		'propertys' => [
			'callableParams' => []
		]
	];
	
	public function __construct (array $exceptionList)
	{
		$this->propertySet('exceptionList', $exceptionList);
		parent::__construct('');
	}
}