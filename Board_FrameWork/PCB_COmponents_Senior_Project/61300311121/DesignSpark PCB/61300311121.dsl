SamacSys ECAD Model
649754/67790/2.32/3/4/Connector

DESIGNSPARK_INTERMEDIATE_ASCII

(asciiHeader
	(fileUnits MM)
)
(library Library_1
	(padStyleDef "c172.5_h115"
		(holeDiam 1.15)
		(padShape (layerNumRef 1) (padShapeType Ellipse)  (shapeWidth 1.725) (shapeHeight 1.725))
		(padShape (layerNumRef 16) (padShapeType Ellipse)  (shapeWidth 1.725) (shapeHeight 1.725))
	)
	(padStyleDef "s172.5_h115"
		(holeDiam 1.15)
		(padShape (layerNumRef 1) (padShapeType Rect)  (shapeWidth 1.725) (shapeHeight 1.725))
		(padShape (layerNumRef 16) (padShapeType Rect)  (shapeWidth 1.725) (shapeHeight 1.725))
	)
	(textStyleDef "Default"
		(font
			(fontType Stroke)
			(fontFace "Helvetica")
			(fontHeight 50 mils)
			(strokeWidth 5 mils)
		)
	)
	(patternDef "HDRV3W95P0X254_1X3_762X254X869" (originalName "HDRV3W95P0X254_1X3_762X254X869")
		(multiLayer
			(pad (padNum 1) (padStyleRef s172.5_h115) (pt 0, 0) (rotation 90))
			(pad (padNum 2) (padStyleRef c172.5_h115) (pt 2.54, 0) (rotation 90))
			(pad (padNum 3) (padStyleRef c172.5_h115) (pt 5.08, 0) (rotation 90))
		)
		(layerContents (layerNumRef 18)
			(attr "RefDes" "RefDes" (pt 0, 0) (textStyleRef "Default") (isVisible True))
		)
		(layerContents (layerNumRef 30)
			(line (pt -1.67 1.595) (pt 6.75 1.595) (width 0.05))
		)
		(layerContents (layerNumRef 30)
			(line (pt 6.75 1.595) (pt 6.75 -1.595) (width 0.05))
		)
		(layerContents (layerNumRef 30)
			(line (pt 6.75 -1.595) (pt -1.67 -1.595) (width 0.05))
		)
		(layerContents (layerNumRef 30)
			(line (pt -1.67 -1.595) (pt -1.67 1.595) (width 0.05))
		)
		(layerContents (layerNumRef 28)
			(line (pt -1.42 1.345) (pt 6.5 1.345) (width 0.1))
		)
		(layerContents (layerNumRef 28)
			(line (pt 6.5 1.345) (pt 6.5 -1.345) (width 0.1))
		)
		(layerContents (layerNumRef 28)
			(line (pt 6.5 -1.345) (pt -1.42 -1.345) (width 0.1))
		)
		(layerContents (layerNumRef 28)
			(line (pt -1.42 -1.345) (pt -1.42 1.345) (width 0.1))
		)
		(layerContents (layerNumRef 18)
			(line (pt 0 1.345) (pt 6.5 1.345) (width 0.2))
		)
		(layerContents (layerNumRef 18)
			(line (pt 6.5 1.345) (pt 6.5 -1.345) (width 0.2))
		)
		(layerContents (layerNumRef 18)
			(line (pt 6.5 -1.345) (pt -1.42 -1.345) (width 0.2))
		)
		(layerContents (layerNumRef 18)
			(line (pt -1.42 -1.345) (pt -1.42 0) (width 0.2))
		)
	)
	(symbolDef "61300311121" (originalName "61300311121")

		(pin (pinNum 1) (pt 0 mils 0 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -25 mils) (rotation 0]) (justify "Left") (textStyleRef "Default"))
		))
		(pin (pinNum 2) (pt 0 mils -100 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -125 mils) (rotation 0]) (justify "Left") (textStyleRef "Default"))
		))
		(pin (pinNum 3) (pt 0 mils -200 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -225 mils) (rotation 0]) (justify "Left") (textStyleRef "Default"))
		))
		(line (pt 200 mils 100 mils) (pt 600 mils 100 mils) (width 6 mils))
		(line (pt 600 mils 100 mils) (pt 600 mils -300 mils) (width 6 mils))
		(line (pt 600 mils -300 mils) (pt 200 mils -300 mils) (width 6 mils))
		(line (pt 200 mils -300 mils) (pt 200 mils 100 mils) (width 6 mils))
		(attr "RefDes" "RefDes" (pt 650 mils 300 mils) (justify Left) (isVisible True) (textStyleRef "Default"))

	)
	(compDef "61300311121" (originalName "61300311121") (compHeader (numPins 3) (numParts 1) (refDesPrefix J)
		)
		(compPin "1" (pinName "1") (partNum 1) (symPinNum 1) (gateEq 0) (pinEq 0) (pinType Bidirectional))
		(compPin "2" (pinName "2") (partNum 1) (symPinNum 2) (gateEq 0) (pinEq 0) (pinType Bidirectional))
		(compPin "3" (pinName "3") (partNum 1) (symPinNum 3) (gateEq 0) (pinEq 0) (pinType Bidirectional))
		(attachedSymbol (partNum 1) (altType Normal) (symbolName "61300311121"))
		(attachedPattern (patternNum 1) (patternName "HDRV3W95P0X254_1X3_762X254X869")
			(numPads 3)
			(padPinMap
				(padNum 1) (compPinRef "1")
				(padNum 2) (compPinRef "2")
				(padNum 3) (compPinRef "3")
			)
		)
		(attr "Manufacturer_Name" "Wurth Elektronik")
		(attr "Manufacturer_Part_Number" "61300311121")
		(attr "RS Part Number" "1725145")
		(attr "RS Price/Stock" "http://uk.rs-online.com/web/p/products/1725145")
		(attr "Arrow Part Number" "61300311121")
		(attr "Arrow Price/Stock" "http://uk.rs-online.com/web/p/products/1725145")
		(attr "Description" "HEADER 3 POSITION 2.54MM 0.100" VERTICLE UNSHROUDED BREAKAWAY THROUGH-HOLE")
		(attr "Datasheet Link" "http://katalog.we-online.de/em/datasheet/6130xx11121.pdf")
		(attr "Height" "8.69 mm")
	)

)
