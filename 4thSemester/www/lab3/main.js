let words = ['ability','about','above','accept','according','account','across','action','activity','actually','address','administration','admit','adult','affect','after','again','against','agency','agent','agree','agreement','ahead','allow','almost','alone','along','already','although','always','American','among','amount','analysis','animal','another','answer','anyone','anything','appear','apply','approach','argue','around','arrive','article','artist','assume','attack','attention','attorney','audience','author','authority','available','avoid','beautiful','because','become','before','begin','behavior','behind','believe','benefit','better','between','beyond','billion','black','blood','board','break','bring','brother','budget','build','building','business','camera','campaign','cancer','candidate','capital','career','carry','catch','cause','center','central','century','certain','certainly','chair','challenge','chance','change','character','charge','check','child','choice','choose','church','citizen','civil','claim','class','clear','clearly','close','coach','collection','college','color','commercial','common','community','company','compare','computer','concern','condition','conference','Congress','consider','consumer','contain','continue','control','could','country','couple','course','court','cover','create','crime','cultural','culture','current','customer','daughter','death','debate','decade','decide','decision','defense','degree','democratic','describe','design','despite','detail','determine','develop','development','difference','different','difficult','dinner','direction','director','discover','discuss','discussion','disease','doctor','dream','drive','during','early','economic','economy','education','effect','effort','eight','either','election','employee','energy','enjoy','enough','enter','entire','environment','environmental','especially','establish','evening','event','every','everybody','everyone','everything','evidence','exactly','example','executive','exist','expect','experience','expert','explain','factor','family','father','federal','feeling','field','fight','figure','final','finally','financial','finger','finish','first','floor','focus','follow','force','foreign','forget','former','forward','friend','front','future','garden','general','generation','glass','government','great','green','ground','group','growth','guess','hanged','hanging','hangman','happen','happy','health','heart','heavy','herself','himself','history','hospital','hotel','house','however','human','hundred','husband','identify','image','imagine','impact','important','improve','include','including','income','increase','indeed','indicate','individual','industry','information','inside','instead','institution','interest','interesting','international','interview','investment','involve','issue','itself','kitchen','knowledge','language','large','later','laugh','lawyer','leader','learn','least','leave','letter','level','light','likely','listen','little','local','machine','magazine','maintain','major','majority','manage','management','manager','market','marriage','material','matter','maybe','measure','media','medical','meeting','member','memory','mention','message','method','middle','might','military','million','minute','mission','model','modern','moment','money','month','morning','mother','mouth','movement','movie','music','myself','nation','national','natural','nature','nearly','necessary','network','never','night','north','nothing','notice','number','occur','offer','office','officer','official','often','operate','opportunity','option','order','organization','other','others','ourselves','outside','owner','paint','paper','parent','participant','particular','party','patient','peace','people','perform','performance','perhaps','period','person','personal','phone','physical','picture','piece','place','plant','player','point','police','policy','political','popular','population','position','positive','possible','power','practice','prepare','present','president','press','pressure','pretty','prevent','price','private','probably','problem','process','produce','product','production','professional','professor','program','project','property','protect','prove','provide','public','purpose','quality','question','quick','quickly','quite','radio','raise','range','rather','reach','ready','reality','realize','really','reason','receive','recent','recently','recognize','record','reduce','reflect','region','relate','relationship','religious','remain','remember','remove','report','represent','require','research','resource','respond','response','responsibility','result','return','reveal','right','scene','school','science','scientist','score','search','season','second','secret','section','security','senior','sense','series','serious','serve','service','seven','several','sexual','shake','share','shoot','short','should','shoulder','significant','similar','simple','simply','since','single','sister','situation','skill','small','smile','social','society','somebody','someone','something','sometimes','sorry','sound','south','space','speak','special','specific','speech','spend','sport','spring','staff','stage','stand','standard','start','state','statement','station','still','store','story','strategy','street','strong','structure','student','study','stuff','style','subject','success','successful','suddenly','suffer','suggest','summer','support','surface','system','table','teach','teacher','technology','television','thank','their','themselves','theory','there','these','thing','think','third','those','though','thought','thousand','threat','three','through','throughout','throw','today','together','tonight','total','tough','toward','trade','traditional','training','travel','treat','trial','trouble','truth','under','understand','until','usually','value','various','victim','victory','video','violence','visit','voice','watch','water','weather','weight','whatever','where','whether','which','while','white','whole','whose','window','within','without','woman','wonder','worker','world','worry','would','write','writer','wrong','young','yourself','youth','yesterday'];

let misses, correct, word, wordsplit;

let canvas = document.getElementById("gallows");
let ctx = canvas.getContext("2d")
ctx.lineWidth = 3;

const rows = [
    ['q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p'],
    ['a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l'],
    ['z', 'x', 'c', 'v', 'b', 'n', 'm']
    ];

    
const keyboard = document.getElementById("keyboard");

rows.forEach(row => {
    const rowDiv = document.createElement('div');
    rowDiv.className = 'keyboard-row';

    row.forEach(letter => {
        const key = document.createElement('button');
        key.className = 'key';
        key.id = 'key-' + letter;
        key.textContent = letter.toUpperCase();
        key.onclick = function() {guess(letter);};
        rowDiv.appendChild(key);
    });

    keyboard.appendChild(rowDiv);
});

function init() {
    let wordid = Math.floor(Math.random() * words.length);
    word = words[wordid];
    if (localStorage.length > 0) {
        word = words[localStorage.getItem("word")];
    } else {
        localStorage.setItem("word", wordid);
    }

    wordsplit = word.toUpperCase().split("");
    
    const answer = document.getElementById("answer");
    answer.innerHTML = "";

    for (let i in wordsplit) {
        const letterDiv = document.createElement('div');
        letterDiv.className = 'letterbox';
        
        const letterp = document.createElement('p');
        letterp.className = "letter";
        letterp.id = 'letter' + i;
        letterDiv.appendChild(letterp);
    
        answer.appendChild(letterDiv);
    }
        
    misses = 0;
    correct = 0;

    ctx.clearRect(0, 0, canvas.width, canvas.height);

    const results = document.getElementById("end");
    results.style.display = "none";

    rows.forEach(row => {
        row.forEach(letter => {
            const button = document.getElementById("key-" + letter);
            button.style.backgroundColor = "rgb(232, 232, 232)";
            button.style.color = "black";
            button.style.cursor = "pointer";
            button.disabled = false;
            if (localStorage.getItem(letter)) {
                guess(letter);
            }
        });
    });
}

init();

function guess(letter) {
    const key = document.getElementById('key-' + letter);
    localStorage.setItem(letter, true);
    // weird blue required for the assignment 
    // key.style.backgroundColor = "blue";
    // key.style.color = "blue";
    // normal configuration
    key.style.color = "rgb(232, 232, 232)";
    key.style.cursor = "default"
    key.disabled = true;

    if (word.includes(letter)) {
        for (let i in wordsplit) {
            if (word[i] == letter) {
                document.getElementById("letter" + i).textContent = wordsplit[i];
                correct++;
            }
        }
        if (correct == word.length) {
            win();
        }
    } else {
        draw();

        if (misses == 9) {
            lose();
        }
    }
}

function draw() {
    ctx.beginPath();
    
    switch (misses) {
        case 0:
            ctx.arc(100, 100, 30, 0, 2 * Math.PI)
            break;
        case 1:
            ctx.moveTo(100, 130);
            ctx.lineTo(100, 210);
            break;
        case 2:        
            ctx.moveTo(100, 210);
            ctx.lineTo(70, 280);

            ctx.moveTo(100, 210);
            ctx.lineTo(130, 280);
            break;
        case 3:
            ctx.moveTo(100, 140);
            ctx.lineTo(80, 210);

            ctx.moveTo(100, 140);
            ctx.lineTo(120, 210);
            break;
        case 4:
            ctx.moveTo(300, 300);
            ctx.lineTo(150, 300);
            break;
        case 5:
            ctx.moveTo(250, 300);
            ctx.lineTo(250, 0);
            break;
        case 6:
            ctx.moveTo(250, 0);
            ctx.lineTo(100, 0);
            break;
        case 7:
            ctx.moveTo(175, 0);
            ctx.lineTo(250, 75);
            break;
        case 8:
            ctx.moveTo(100, 0);
            ctx.lineTo(100, 70);

            ctx.moveTo(85, 85);
            ctx.lineTo(95, 95);

            ctx.moveTo(95, 85);
            ctx.lineTo(85, 95);

            ctx.moveTo(115, 85);
            ctx.lineTo(105, 95);

            ctx.moveTo(105, 85);
            ctx.lineTo(115, 95);
            break;
        default:
            break;
    }
    ctx.stroke();

    misses++;
}

function end() {
    localStorage.clear();

    rows.forEach(row => {
        row.forEach(letter => {
            const button = document.getElementById("key-" + letter);
            button.disabled = true;
        });
    });

    const ans = document.getElementById("ans");
    ans.textContent = "The word was " + word.charAt(0).toUpperCase() + word.slice(1);

    const results = document.getElementById("end");
    results.style.display = "flex";

    const correctField = document.getElementById("correct");
    correctField.textContent = "Correct letters: " + correct + "/" + word.length;
    
    const missesField = document.getElementById("misses");
    missesField.textContent = "Misses: " + misses + "/9";
}

function lose() {
    const resultField = document.getElementById("result");
    resultField.textContent = "You lose!";

    end();
}

function win() {
    const resultField = document.getElementById("result");
    resultField.textContent = "You win!";
    end();
}

function giveUp() {
    localStorage.clear();
    init();
}