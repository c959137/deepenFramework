<?php
namespace m5D02F22739AA11E4B3C6005056847E34\databases\exceptions;
use \m5D02F22739AA11E4B3C6005056847E34\databases\exceptions\exceptionClass as _exceptionClass;
class executeExceptionClass extends _exceptionClass
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
		parent::__construct(empty($exceptionInstance) ? '資料庫查詢發生錯誤' : $exceptionInstance->getMessage(), empty($exceptionInstance) ? 0 : $exceptionInstance->getCode());
	}
}
