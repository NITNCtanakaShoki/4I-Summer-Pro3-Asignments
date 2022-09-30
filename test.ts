import InputLoop from "https://deno.land/x/input@2.0.3/index.ts";
import { CProgramFile } from "./tests/CProgramFile.ts"
import { print, println, CC } from "./tests/print.ts"
import { download, downloadSample } from "./tests/download.ts"
import test = Deno.test

const input = new InputLoop()
const compiler: string = await input.question("コンパイラ (cc? or gcc?):")
const attendNumber: string = await input.question("出席番号:")
const sampleDirectory = "./samples/"
const samples = [1, 2, 3, 4, 5, 6].map( num => `sample${num}.pgm`)


await downloadSample(samples)

const testCases = [
    // { name: "2chi", arg: 1 },
    { name: "nega", arg: 1 },
    { name: "jouge", arg: 1 },
    { name: "sayuu", arg: 1 },
    { name: "180", arg: 1 },
    { name: "90", arg: 1 },
    { name: "270", arg: 1 },
    { name: "yoko", arg: 2 },
    { name: "tate", arg: 2 },
    { name: "in", arg: 2 },
]

await download(testCases.map(test => test.name))

const argOne = async (expected: CProgramFile, actual: CProgramFile) => {
    for (const sample of samples) {
        print(`    ${sample}: `)
        const expectedData = await expected.exec(compiler, "expected", sampleDirectory + sample)
        const actualData = await actual.exec(compiler, "actual", sampleDirectory + sample)
        const result = expectedData.faileReason(actualData)
        if (result === null) {
            println("OK", CC.GREEN)
        } else {
            println(`FAIL, ${result}`, CC.RED)
        }
    }
}

const argTwo = async (expected: CProgramFile, actual: CProgramFile) => {
    for (const sample1 of samples) {
        for (const sample2 of samples) {
            print(`    ${sample1} & ${sample2}: `)
            const expectedData = await expected.exec(compiler, "expected", sampleDirectory + sample1, sampleDirectory + sample2)
            const actualData = await actual.exec(compiler, "actual", sampleDirectory + sample1, sampleDirectory + sample2)
            const result = expectedData.faileReason(actualData)
            if (result === null) {
                println("OK", CC.GREEN)
            } else {
                println(`FAIL, ${result}`, CC.RED)
            }
        }
    }
}


for (const testCase of testCases) {
    println("=================================")
    println(`case: ${testCase.name}`)
    const actualProgram = new CProgramFile(`${attendNumber}-${testCase.name}.c`)
    if (!(await actualProgram.isExist())) {
        println("    FAIL: ファイルが存在しません", CC.YELLOW)
        continue
    }
    const expectedProgram = new CProgramFile(`expecteds/22-${testCase.name}.c`)
    if (testCase.arg === 1) {
        await argOne(expectedProgram, actualProgram)
    } else {
        await argTwo(expectedProgram, actualProgram)
    }
}
await Promise.all([
    Deno.remove("samples", { recursive: true }),
    Deno.remove("expecteds", { recursive: true }),
    Deno.remove("a.out"),
    Deno.remove("expected"),
    Deno.remove("actual")
])
println("=================================")