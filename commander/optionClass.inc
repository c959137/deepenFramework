<?php
namespace m5D02F22739AA11E4B3C6005056847E34\commander;

class optionClass
{
    public $flags = [];
    public $desc;
    public $long;
    public $short;
    public $optional = false;
    public $required = false;

    public function __construct($flags, $desc = '')
    {
        $this->rawFlags = $flags;
        $this->flags = preg_split("/[\s,]+/", $flags);
        $this->desc = $desc;

        $this->addLongAndShort();

        if (strpos($flags, '[') !== false) {
            $this->optional = true;
        } else if (strpos($flags, '<') !== false) {
            $this->required = true;
        }

    }

    public function addLongAndShort()
    {
        if (count($this->flags) > 1) {
            $this->short = $this->flags[0];
            $this->long = $this->flags[1];
        }
    }


    public function getName()
    {
        return preg_replace('/--/', '', $this->long);
    }

    public function is($arg)
    {
        return $arg === $this->long || $arg === $this->short;
    }
}