<?php
namespace m5D02F22739AA11E4B3C6005056847E34\databases\exceptions;
\m5D02F22739AA11E4B3C6005056847E34\applicationFrameworkClass::classLoader('exceptionClass', 'exceptions');
class exceptionClass extends \m5D02F22739AA11E4B3C6005056847E34\exceptions\exceptionClass
{
	public function __construct($message = '資料庫操作發生問題')
	{
		parent::__construct($message);
	}
}

class queryExceptionClass extends exceptionClass
{
	use \m5D02F22739AA11E4B3C6005056847E34\traits\propertysClass;
	private $_instanceParams = [
		'propertys' => [
			'sqlScript' => [
				'get' => true,
				'set' => false,
			],
			'previous' => [
				'get' => true,
				'set' => false,
			],
		]
	];
	public function __construct($sqlScript, \PDOException $exceptionInstance = null)
	{
		$this->propertySet('sqlScript', $sqlScript);
		$this->propertySet('previous', $exceptionInstance);
		parent::__construct(empty($exceptionInstance) ? '資料庫查詢發生錯誤' : $exceptionInstance->getMessage());
	}
}
