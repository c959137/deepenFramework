<?php
namespace m5D02F22739AA11E4B3C6005056847E34\databases\exceptions;
use \m5D02F22739AA11E4B3C6005056847E34\exceptions\exceptionClass as _exceptionClass;
class exceptionClass extends _exceptionClass
{
	public function __construct($message = '資料庫操作發生問題', $code = 0)
	{
		parent::__construct($message, $code);
	}
}