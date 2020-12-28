const addon = require("bindings")("addon.node");
const express = require("express");
const path = require('path');
const handlebars = require('express-handlebars');

const app = express();// create the express app

// Let the app handle json and urlencoded input
app.use(express.json());
app.use(express.urlencoded({
    extended: false
}));

// Initialize/set the Handlesbars instance/render engine
const handlebars_inst = handlebars.create({
    extname: '.handlebars',
    compilerOptions: {
        preventIndent: true
    },
    layoutsDir: path.join(__dirname, 'views', 'layouts'),
    partialsDir: path.join(__dirname, 'views', 'partials')
});
app.engine('handlebars', handlebars_inst.engine);
app.set('view engine', 'handlebars');
app.set('views', path.join(__dirname, 'views', 'pages'));


// Converts an operator to the C++ function associated with that operator
const funcMap = {
    "+": addon.add,
    "-": addon.minus,
    "*": addon.times,
    "/": addon.divide,
    "<<": addon.toCBNS,
    "<": addon.toComplex,

};

// TODO - Have the user enter the calculation into a single textbox, parse that into the basic steps and then call the C++ addon functions
// TODO - Let the user store values inside of variables
// TODO - Let the user define functions that they can use
app.route('/')
    .get((req, res) => {
        res.status(200).render('page');
    })
    .post((req, res) => {

        // Acquire the new inputs
        let A_real = String(req.body.A_real);
        let A_imag = String(req.body.A_imag);
        let operation = req.body.operation;
        let B_real = String(req.body.B_real);
        let B_imag = String(req.body.B_imag);
        let C_real = String(req.body.C_real);
        let C_imag = String(req.body.C_imag);
        let str = String(req.body.str);
        let input_text = String(req.body.input_text);
        
        // Re-render the values the user provided
        res.locals.form = {
            "A_real": A_real,
            "A_imag": A_imag,
            "operation": operation,
            "B_real": B_real,
            "B_imag": B_imag,
            "C_real": C_real,
            "C_imag": C_imag,
            "str": str
        };

        // Check if the operation is a valid/supported one - either give answer or give an alert
        if(!(operation in funcMap)){
            res.locals.alert = {"title": "Operation mismatch",'message': `Operation "${operation}" not supported`};
            res.render('page');
        } else {
            // The addons can throw errors, so catch them
            try {
                let answer = funcMap[operation](Number(A_real), Number(A_imag), Number(B_real), Number(B_imag), Number(C_real), Number(C_imag), str);
                res.locals.answer = answer + input_text;
            } catch (e){
                res.locals.alert = {"title": "Operation Error", "message": e};
            }
            res.render('page');
        }
    }
);


app.listen(process.env.PORT || 5000, () => {
    console.log('express app running at http://localhost:5000/')
});


