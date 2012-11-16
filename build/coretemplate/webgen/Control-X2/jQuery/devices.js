{
	$('document').ready(function() 
	{ 
		//Assign default value to form field #1

                $.getJSON('/cgi-bin/uenvtmp.cgi',
			function(data){
                	document.Testform.Feld1.checked = (data.relay1 == 1);
                	document.Testform.Feld2.checked = (data.relay2 == 1);
                	document.Testform.Feld3.checked = (data.relay3 == 1);
                	document.Testform.Feld4.checked = (data.relay4 == 1);

		});
                $.getJSON('/cgi-bin/uenv.cgi',
			function(data){
			$('#tfeld1').text(data.relname1);
			$('#tfeld2').text(data.relname2);
			$('#tfeld3').text(data.relname3);
			$('#tfeld4').text(data.relname4);

		});


		// an anchor element in the list 'mylist' gets clicked
		$('.target').change(function() {
			// the ID of the record we need to retrieve is stored in the rel element, so we fetch it first
                        var id = $(this).attr('value');
			$.post('/cgi-bin/dodev.cgi', 
				{ 
					'Feld' : $(this).attr('value'),
					'Value': $(this).attr('checked')
				}, parseInfo);
		});
	});
	
	// this function parses the fetched data into the 'info' paragraph
	function parseInfo(data)
	{
		// the data parameter is an object, while name and email are the keys from the PHP array
		// you can also use the 'text' function instead of html. The difference is that 'text'
		// displays raw text, even if it contains other HTML elements.
		//$('#info').html(data);
	}
}
