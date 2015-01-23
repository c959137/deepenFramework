<?php
namespace m5D02F22739AA11E4B3C6005056847E34\databases;
class databaseManagerClass
{
	use \m5D02F22739AA11E4B3C6005056847E34\traits\arrayPathClass;

	const CONNECTION_TYPE_PDO = 'pdo';
	private static $_staticParams = [];
	
	public static function connectionInstance($connectionName, $connectionType = self::CONNECTION_TYPE_PDO, $connectionInformation)
	{
		$keyName = __FUNCTION__;
		if (!isset(self::$_staticParams[$keyName])) {
			self::$_staticParams[$keyName] = [];
		}
		
		if (!isset(self::$_staticParams[$keyName][$connectionName])) {
			switch ($connectionType) {
				case self::CONNECTION_TYPE_PDO :
					$className = static::classLoader('connectionClass', 'pdo');
					break;
					
				default : 
					xxx();
					break;
			}
			self::$_staticParams[$keyName][$connectionName] = [
				'instance' => new $className($connectionInformation),
			];
		}
		return self::$_staticParams[$keyName][$connectionName]['instance'];
	}

	protected static function classLoader($className, $middleNs = '')
	{
		$keyName = __FUNCTION__;
		if (!isset(self::$_staticParams[$keyName])) {
			self::$_staticParams[$keyName] = [];
		}
		if (!isset(self::$_staticParams[$keyName][$className])) {
			$moduleClass = \m5D02F22739AA11E4B3C6005056847E34\applicationFrameworkClass::moduleClassLoaderByPath(__FILE__);
			$middleNs =  static::pathToNs(__FILE__, ['pdo']);
			$fullClassName = $moduleClass::classLoader($className, $middleNs);
			self::$_staticParams[$keyName][$className] = $fullClassName;
		}
		return $fullClassName;
	}
}

abstract class connectionAbstractClass1 {
	use	\m5D02F22739AA11E4B3C6005056847E34\traits\propertysClass;
	private $_instanceParams = [];
	
	protected function serverInstanceGet()
	{
		$keyName = __FUNCTION__;
		if (!isset($this->_instanceParams[$keyName])) {
			$this->_instanceParams[$keyName] = $this->doServerInstance();
		}
		return $this->_instanceParams[$keyName];
	}
	abstract protected function doServerInstance();
	
	public function query($sqlScript)
	{
		try {
			return $this->doQuery($sqlScript);
		} catch (m5D02F22739AA11E4B3C6005056847E34\databases\exceptions\exceptionClass $exceptionInstance) {
xxx();
			throw $exceptionInstance;
		} catch (exception $exceptionInstance) {
			var_dump($exceptionInstance);
			xxx();
		}
	}
	abstract protected function doQuery($sqlScript);

	public function encodeData($value)
	{
		return addslashes($value);
	}
	
	public function execute($sqlScript)
	{
		try {
			return $this->doExecute($sqlScript);
		} catch (m5D02F22739AA11E4B3C6005056847E34\databases\exceptions\exceptionClass $exceptionInstance) {
			throw $exceptionInstance;
		} catch (exception $exceptionInstance) {
			var_dump($exceptionInstance);
			xxx();
		}
	}
	abstract protected function doExecute($sqlScript);
	
	/**
	* @brief 交易是否進行中
	* @return boolean 
	* @author nico chen 2015-01-22
	* @version 0.00.01
	* \b CHANGE \b HISTORY: <br>	 
	*   <b>- nico chen / 2015-01-22</b>    
	*      - 建立函數			
	*/
	protected function transactionProcessingGet()
	{
		$keyName = static::propMethodNameToKeyName(__FUNCTION__);
		return isset($this->_instanceParams[$keyName]) ? $this->_instanceParams[$keyName] : false;
	}
	
	public function begin()
	{
		$keyName = 'transactionProcessing';
		$this->_instanceParams[$keyName] = $this->doBegin();
		return $this->_instanceParams[$keyName];
	}
	abstract protected function doBegin();

	public function commit()
	{
		return $this->doCommit();
	}
	abstract protected function doCommit();

	public function rollback()
	{
		return $this->doRollback();
	}
	abstract protected function doRollback();
	
}

abstract class recordsetAbstractClass
{
	use	\m5D02F22739AA11E4B3C6005056847E34\traits\propertysClass;
	private $_instanceParams = [];
	public function __construct()
	{
	}
	
	public function fetchRow()
	{
		return $this->doFetchRow();
	}
	abstract protected function doFetchRow();
}

namespace m5D02F22739AA11E4B3C6005056847E34\databases\pdo;
class recordsetClass extends \m5D02F22739AA11E4B3C6005056847E34\databases\recordsetAbstractClass
{
	use	\m5D02F22739AA11E4B3C6005056847E34\traits\propertysClass;
	private $_instanceParams = [
		'propertys' => [
			'statementInstance' => [
				'get' => true,
				'set' => false,
			],
			'rowData' => [
				'get' => true,
				'set' => false,
			],
			
		],
	];
	public function __construct(\PDOStatement $statementInstance)
	{
		$this->propertySet('statementInstance', $statementInstance);
		$statementInstance->setFetchMode(\PDO::FETCH_ASSOC);
		parent::__construct();
	}
	
	protected function doFetchRow()
	{
		$statementInstance = $this->statementInstance;
		$this->propertySet('rowData', $statementInstance->fetch());
		return $this->rowData;
	}
}

class connectionClass1 extends  \m5D02F22739AA11E4B3C6005056847E34\databases\connectionAbstractClass1 {
	private $_instanceParams = [];
	
	protected function doServerInstance()
	{
		$drive = 'mysql';
		$dbname = 'gameCenter';
		$host = '192.168.100.50';
		$username = 'gameCenterRoot';
		$password = 'PmoJcZc21K';
		$dsn = "{$drive}:dbname={$dbname}; host={$host}";
		$driverOptions = [
			\PDO::ATTR_ERRMODE => \PDO::ERRMODE_EXCEPTION
		];
		$serverInstance = new \PDO($dsn, $username, $password, $driverOptions);
		$serverInstance->query('SET NAMES UTF8');
		return $serverInstance;
	}

	protected function doQuery($sqlScript){
		try {
			$statementInstance = $this->serverInstance->query($sqlScript);
			if ($statementInstance instanceof \PDOStatement) {
				return new recordsetClass($statementInstance);
			} else {
				throw new \m5D02F22739AA11E4B3C6005056847E34\databases\exceptions\queryExceptionClass($sqlScript);
			};
		} catch (\PDOStatement $exceptionInstance) {
xxx();
			throw new \m5D02F22739AA11E4B3C6005056847E34\databases\exceptions\queryExceptionClass($sqlScript, $exceptionInstance);
		} catch (\exception $exceptionInstance) {
			throw $exceptionInstance;
		}
	}

	protected function doExecute($sqlScript) 
	{
		$statementInstance = $this->serverInstance->prepare($sqlScript);
		if ($statementInstance->execute()) {
			return new recordsetClass($statementInstance);
		} else {
			throw new \m5D02F22739AA11E4B3C6005056847E34\databases\exceptions\queryExceptionClass($sqlScript);
		};
	}

	public function encodeData($value)
	{
		return $this->serverInstance->quote($value);
	}
	
	protected function doBegin() 
	{
		return $this->serverInstance->beginTransaction();
	}

	protected function doCommit() 
	{
		return $this->serverInstance->commit();
	}

	protected function doRollback() 
	{
		return $this->serverInstance->rollBack();
	}
}

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
