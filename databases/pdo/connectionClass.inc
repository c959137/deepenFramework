<?php
namespace m5D02F22739AA11E4B3C6005056847E34\databases\pdo;

\m5D02F22739AA11E4B3C6005056847E34\applicationFrameworkClass::classLoader('connectionAbstractClass', 'databases');
class connectionClass extends  \m5D02F22739AA11E4B3C6005056847E34\databases\connectionAbstractClass {
	private $_instanceParams = [];
	
	protected function doServerInstance()
	{
		$connectionInformation = $this->connectionInformation;
		$drive = 'mysql';
		$dbname = $connectionInformation['db'];
		$host = $connectionInformation['host'];
		$username = $connectionInformation['username'];
		$password = $connectionInformation['password'];
		$port = isset($connectionInformation['port']) ? $connectionInformation['port'] : '3306';
		$dsn = "{$drive}:dbname={$dbname}; host={$host}; port={$port}";
		$driverOptions = [
			\PDO::ATTR_ERRMODE => \PDO::ERRMODE_EXCEPTION,
			\PDO::MYSQL_ATTR_INIT_COMMAND => 'SET NAMES utf8'
		];
		$serverInstance = new \PDO($dsn, $username, $password, $driverOptions);
		//$serverInstance->query('SET NAMES UTF8');
		return $serverInstance;
	}

	protected function doQuery($sqlScript){
		try {
			$statementInstance = $this->serverInstance->query($sqlScript);
			if ($statementInstance instanceof \PDOStatement) {
				$recordsetClass = \m5D02F22739AA11E4B3C6005056847E34\applicationFrameworkClass::classLoader('recordsetClass', 'databases\pdo', '5D02F22739AA11E4B3C6005056847E34');
				return new $recordsetClass($statementInstance);
			} else {
				\m5D02F22739AA11E4B3C6005056847E34\applicationFrameworkClass::classLoader('queryExceptionClass', 'databases\exceptions', '5D02F22739AA11E4B3C6005056847E34');
				throw new \m5D02F22739AA11E4B3C6005056847E34\databases\exceptions\queryExceptionClass($sqlScript);
			};
		} catch (\PDOException $exceptionInstance) {
			\m5D02F22739AA11E4B3C6005056847E34\applicationFrameworkClass::classLoader('queryExceptionClass', 'databases\exceptions', '5D02F22739AA11E4B3C6005056847E34');
			throw new \m5D02F22739AA11E4B3C6005056847E34\databases\exceptions\queryExceptionClass($sqlScript, $exceptionInstance);
		} catch (\exception $exceptionInstance) {
			throw $exceptionInstance;
		}
	}

	protected function doExecute($sqlScript) 
	{
		$statementInstance = $this->serverInstance->prepare($sqlScript);
		if ($statementInstance->execute()) {
			$recordsetClass = \m5D02F22739AA11E4B3C6005056847E34\applicationFrameworkClass::classLoader('recordsetClass', 'databases\pdo', '5D02F22739AA11E4B3C6005056847E34');
			return new $recordsetClass($statementInstance);
		} else {
			\m5D02F22739AA11E4B3C6005056847E34\applicationFrameworkClass::classLoader('queryExceptionClass', 'databases\exceptions', '5D02F22739AA11E4B3C6005056847E34');
			throw new \m5D02F22739AA11E4B3C6005056847E34\databases\exceptions\queryExceptionClass($sqlScript);
		};
	}

	public function encodeData($value)
	{
		return $this->serverInstance->quote($value);
	}
	
	protected function doBegin() 
	{
		$sql = "
			begin;
		";
		$this->execute($sql);
		return true;
	}

	protected function doCommit() 
	{
		$sql = "
			commit;
		";
		return $this->execute($sql);
	}

	protected function doRollback() 
	{
		$sql = "
			rollback;
		";
		return $this->execute($sql);
	}
	
	protected function doGetAutoCommit()
	{
		$sql = "
			select @@autocommit autoCommit;		
		";
		$recordsetInstance = $this->query($sql);
		$rowData = $recordsetInstance->fetchRow();
		return $rowData['autoCommit'];
	}
	
	protected function doSetAutoCommit($autoCommit)
	{
		static $maps = [
			0 => 1,
			1 => 0
		];
		 static $maps2 = [
			true => 1,
			false => 0,
		 ];
		$commit = $this->autoCommit;
		if ($maps[$autoCommit] == $maps[$commit]) {
			return ;
		}
		
		$autoCommitSw = ($autoCommit) ? '1' : '0';
		$sql = "
			SET AUTOCOMMIT={$autoCommitSw};
		";
		$this->execute($sql);
	}
	
	/*
		取得程序鎖定
	**/
	public function lock($lockName, $timeout = 10)
	{
		$recordsetInstance = $this->query("select get_lock ('{$lockName}', {$timeout}) lockStatus;");
		$rowData = $recordsetInstance->fetchRow();
		$recordsetInstance->statementInstance->closeCursor();
		if ($rowData['lockStatus'] === 0) {
			throw new \exception('無法取得程序鎖定');
		}
	}
	
	/*
		取得程序鎖定
	**/
	public function unLock($lockName)
	{
		$recordsetInstance = $this->query("select RELEASE_LOCK ('{$lockName}') lockStatus;");
		$rowData = $recordsetInstance->fetchRow();
		$recordsetInstance->statementInstance->closeCursor();
		if ($rowData['lockStatus'] === 0) {
			throw new \exception('無法取得程序鎖定');
		}
	}	
}