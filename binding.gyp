{
  "targets": [
    {
      "target_name": "usergroup",
      "sources": [ "usergroup.cpp" ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ]
    }
  ]
}