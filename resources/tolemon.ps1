Get-ChildItem -Path . -Filter *.png | ForEach-Object {
	$originalFile = $_.FullName
	$fileName = $_.Name
    
	if ($fileName -eq "lemon.png")
	{
		Write-Host "Skipping lemon.png"
		return
	}
    
	$dimensions = magick identify -format "%wx%h" $originalFile
    
	if ($dimensions -match "^(\d+)x(\d+)$")
	{
		$width = $Matches[1]
		$height = $Matches[2]
        
		Write-Host "Replacing $fileName (${width}x${height}) with resized lemon.png"
        
		magick lemon.png -resize "${width}x${height}!" $originalFile
	} else
	{
		Write-Warning "Could not parse dimensions for $fileName"
	}
}
